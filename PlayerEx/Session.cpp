#include "Session.h"

#include <algorithm>
#include <iostream>

#include <stdio.h>  /* defines FILENAME_MAX */

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, 0)) != std::string::npos) {
		str.replace(start_pos, from.size(), to);
	}
}
std::string ArrToFileList(std::vector<Player>& vec, std::string& fileEx)
{
	std::string str;
	auto it(vec.begin());
	while (it != vec.end())
	{
		str.append((it == vec.begin() ? "\"" : ", \"") + (*it).getName() + "." + fileEx + "\"");
		it++;
	}
	return str;
}


Session::Session() : _linker(this), server_handler([this] { _linker.run(); })
{
	_load();
}

void Session::parseArgs(std::vector<std::string>& args)
{
	_args = std::queue<std::string>(std::deque<std::string>(args.begin(), args.end()));
}

void Session::save()
{
	_save();
}

void Session::executeTasks()
{
	//if (std::find(_args.begin(), _args.end(), "Repo") != _args.end() || (*_args.end()).find("Repo", 0))
	//need to put that in the front
	while (!_args.empty())
	{
		std::string command = popFront();

		if (command == "-user")
		{
			_user = popFront();
		} 
		else if (command == "-setColor")
		{
			std::string name = popFront(),
						color = popFront();
			std::transform(name.begin(), name.end(), name.begin(), ::tolower);
			Player nullPlayer(name);
			auto pos = std::find(_players.begin(), _players.end(), nullPlayer);

			if (pos != _players.end())
			{
				(*pos).setColorFromString(color);
			}
			else
				_players.push_back(Player(name, color));
		}
		else if(command == "-removePlayer")
		{
			std::string name = popFront();
			Player nullPlayer(name);
			auto pos = std::find(_players.begin(), _players.end(), nullPlayer);

			if (pos != _players.end())
			{
				_players.erase(pos);
			}

			if (std::remove(std::string("intermediates/" + name + ".css").c_str()))
				std::cout << "Something went wrong while clearing. CSS was not generated or file was still in Use" << std::endl;
		}
		else if(command == "-listPlayers")
		{
			for (auto it = _players.begin(); it < _players.end(); it++)
				std::cout << (*it).getName() << "\t\t\t" << (*it).getColorHex() << std::endl;
		}
		else if(command == "-loadRepo")
		{
			std::cout << command + " is currently not implemented" << std::endl;
		}
		else if(command == "-resetRepo")
		{
			std::cout << command + " is currently not implemented" << std::endl;
		}
		else if(command == "-setBrowser")
		{
			std::cout << command + " is currently not implemented" << std::endl;
		}
		else if(command == "-addMissing")
		{
			std::cout << command + " is currently not implemented" << std::endl;
		}
		else if(command == "-addBackground")
		{
			std::cout << command + " is currently not implemented" << std::endl;
		}
		else if(command == "-addBackground")
		{
			std::cout << command + " is currently not implemented" << std::endl;
		}
		else if (command == "-removeBackground")
		{
			std::cout << command + " is currently not implemented" << std::endl;
		}
		else if (command == "-disableBackground")
		{
			std::cout << command + " is currently not implemented" << std::endl;
		}
		else if (command == "-updateBrowser")
		{
			generateCSS();
		}
		else if (command == "-save")
		{
			_save();
		}
		else if (command == "-registerCommand")
		{
			std::cout << command + " is currently not implemented" << std::endl;
		}
		else if (command == "-test")
		{

		}
		else
		{
			std::cout << "Unknown command: " << command << std::endl;
		}
	}
}


Session::~Session()
{
	_linker.~ExtensionLinker();
	if (server_handler.joinable())
		server_handler.join();
	_save();
}

void Session::_save()
{
	std::ofstream usrData("userdata.dat");

	std::string usrStr = _user + "\n";
	usrData.write(usrStr.c_str(), usrStr.size()); //first line is User
	//after that there follows the Player Data List
	for (auto it = _players.begin(); it < _players.end(); it++)
	{
		Player& player = *it;
		std::string data = player.getData() + "\n";
		usrData.write(data.c_str(), data.size());
	}

}

void Session::_load()
{
	std::ifstream usrData("userdata.dat");

	if (!usrData.is_open())
		return;
	bool first = true;
	for (std::string line; std::getline(usrData, line); )
		if (first)
		{
			_user = line;
			first = false;
		}
		else
			_players.push_back(Player(line));
}

void Session::generateCSS()
{
	#if WIN32
		system("del /q /s \"intermediates\\*\"");
	#else
		system("rm -rf \"intermediates\\*\"");
	#endif

	//make reading static so less time is wasted
	std::string genericCSS, selfGenericCSS;
	std::ifstream _generic("assets/generic.css"), _selfGeneric("assets/genericSelf.css");

	for (std::string line; std::getline(_generic, line); )
		genericCSS += line + "\n";
	for (std::string line; std::getline(_selfGeneric, line); )
		selfGenericCSS += line + "\n";

	_generic.close();
	_selfGeneric.close();

	for (auto it = _players.begin(); it < _players.end(); it++)
	{
		Player& player = *it;
		std::string result;
		if (player.getName() == _user)
			result = selfGenericCSS;
		else
			result = genericCSS;
		replaceAll( result, "xxxx", player.getName());
		replaceAll( result, "cccccc", player.getColorHex());

		
		std::ofstream  ofs("intermediates/" + player.getName() + ".css");
		ofs.write(result.data(), result.size());
		ofs.close();
	}

	std::string result;
	for (auto it = _players.begin(); it < _players.end(); it++)
	{
		Player& player = *it;

		std::ifstream  ifs("intermediates/" + player.getName() + ".css");
		for (std::string line; std::getline(ifs, line);)
			result += line;
		ifs.close();
	}
	_linker.sendCSS("c" + result);
}

std::string Session::popFront()
{
	if (_args.empty())
		return "";
	std::string str(_args.front());
	_args.pop();
	return str;
}
