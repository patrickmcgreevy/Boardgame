#pragma once
#include <utility>

using std::pair;

class Player
{
public:
	Player();
	Player(Player & rOther);
	Player(int newId, pair<int, int> newCoords);
	Player(int newId, int xCoord, int yCoords);
	//Player(Player & rRhs);

	int getID() const;
	pair<int, int> getCoords() const;
	void getCoords(int & rX, int & rY);
	void move(pair<int, int>&rNewCoords);
	void move(int x, int y);

	Player & operator=(const Player & other);
private:
	int id;
	pair<int, int> coords;
};