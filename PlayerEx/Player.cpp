#include "Player.h"

#include <sstream>



Player::Player() : _name(), _color(-1)
{
}

Player::Player(std::string &name, int color) : _name(name), _color(color)
{
}

Player::Player(std::string &name, std::string &color) : _name(name), _color(-1)
{
	setColorFromString(color);
}

Player::Player(std::string &data)
{
	unsigned sep = data.find_first_of('#', 0);
	setName(data.substr(0, sep));
	setColorFromString(data.substr(sep + 1, data.size() - sep));
}

std::string Player::getName()
{
	return _name;
}

int Player::getColor()
{
	return _color;
}

std::string Player::getColorHex()
{
	std::stringstream ss;
	ss << std::hex << _color;
	std::string str(ss.str());
	while (str.size() < 6)
		str.insert(str.begin(), '0');
	return str;
}


void Player::setName(std::string &str)
{
	_name = str;
}

void Player::setColor(int col)
{
	_color = col;
}

void Player::setColorFromString(std::string &str)
{
	_color = strtol(str.data(), nullptr, 16);
}

std::string Player::getData()
{
	return _name + "#" + getColorHex();
}

void Player::save( std::ofstream& ofs)
{
	std::string str(getData() + "/n");
	ofs.write(str.data(), str.size());
}

Player::~Player()
{
}

bool Player::operator==(const Player & other)
{
	if (_name == other._name)
		return true;
	return false;
}