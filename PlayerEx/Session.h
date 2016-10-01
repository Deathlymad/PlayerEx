#include <string>
#include <thread>
#include <queue>
#include <vector>

#include "Player.h"
#include "ExtensionLinker.h"

#pragma once
class Session
{
public:
	Session();

	void parseArgs(std::vector<std::string>& args);

	void save();

	void executeTasks();

	void generateCSS();

	~Session();

private:
	void _save();
	void _load();

	std::string popFront();

	std::vector<Player> _players;
	std::string _user;

	std::queue<std::string> _args;

	ExtensionLinker _linker;
	std::thread server_handler;
};

