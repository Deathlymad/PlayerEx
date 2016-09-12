#include <fstream>
#include <string>

#pragma once
class Player
{
public:
	Player();
	Player(std::string&, int);
	Player(std::string&, std::string&);
	Player(std::string&);

	std::string getName();
	int getColor();
	std::string getColorHex();

	void setName(std::string&);
	void setColor(int);
	void setColorFromString(std::string&);

	std::string getData();
	void save( std::ofstream&);

	~Player();

	bool operator==( const Player& other);

private:
	std::string _name;
	int _color;
};

