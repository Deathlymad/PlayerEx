#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>


#include "Player.h"
#include "Session.h"


//Add Help for Commands
// web support for Path





int main(int argc, char* argv[])
{
	std::vector<std::string> Args(argv, argv + argc);
	Args.erase(Args.begin()); //file Call

	std::cout << "Welcome to the The Player.me Color Generator." << std::endl;

	Session _RuntimeSession;
	while (true)
	{
		_RuntimeSession.parseArgs(Args);
		_RuntimeSession.executeTasks();
		Args.clear();
		char c;
		while ( c = std::cin.get())
		{
			if (c == '\n')
				break;
			std::cin.putback(c);
			std::string str;
			std::cin >> str;
			Args.push_back(str);
		}
	}

	system("pause");
}