#include <string>
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

	~Session();

private:
	void _save();
	void _load();

	void generateCSS();
	void generateExtension();
	void applyExtension();

	std::string popFront();

	std::vector<Player> _players;
	std::string _user;

	std::queue<std::string> _args;

	ExtensionLinker _linker;
};

