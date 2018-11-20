#pragma once
#include <map>
#include <unordered_map>
#include <iostream>
#include <string>
#include <cmath>
#include "player.h"

using std::unordered_map;
using std::map;
using std::string;
using std::abs;
using std::cout;
using std::endl;

class Board
{
public:
	Board();
	Board(const int m);

	bool insert(const int id, const int x, const int y);
	bool addPlayer(Player & rPlayer);
	bool remove(const int id);
	bool find(const int id);
	bool move(const int id, pair<int, int> & rCoords);
	bool move(const int id, const int x, const int y);
	void printByID();

private:
	const unsigned int m;
	unsigned int n;

	unordered_map<string, Player> coordinateMap;
	unordered_map<unsigned int, Player> idMap;
	
	bool pushToCoordMap(const int x, const int y, const Player & rPlayer);
	bool pushToCoordMap(const pair<int, int> & rPair, const Player & rPlayer);
	bool pushToCoordMap(const string & rCoordString, const Player & rPlayer);
	bool pushToIdMap(const unsigned int id, const Player & rPlayer);

	bool validateCoords(pair<int, int> & rCoords);
	bool validateId(int id);
	bool validateNumPlayers();
	bool validateMove(const int id, const pair<int, int> & rCoords);
	bool validateBounds(pair<int, int> & rCoords);

	string & coordPairToString(const pair<int, int> & rPair);

	bool removeFromIdMap(const int id);
	bool removeFromCoordMap(const pair<int, int> & rCoords);
};