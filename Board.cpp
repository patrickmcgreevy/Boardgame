#include "board.h"


Board::Board() : m(0)
{
	n = 0;
}
Board::Board(const int s) : m(s)
{
	n = 0;
}

string & Board::coordPairToString(const pair<int, int> & rPair)
{
	string *coordString = new string();
	//int a = rPair.first, b = rPair.second, c = 10;
	*coordString = std::to_string(rPair.first) + "," + std::to_string(rPair.second);

	return *coordString;
}

bool Board::pushToCoordMap(const string & rCoordString, const Player & rPlayer)
{
	/*if (coordinateMap.emplace(rCoordString, rPlayer).second)
		return true;*/
	coordinateMap[rCoordString] = rPlayer;

	if (coordinateMap[rCoordString].getID() == rPlayer.getID())
		return true;

	cout << "Pushing to the coordinate map TESTTESTfailed." << endl;
	return false;
}

bool Board::pushToCoordMap(const pair<int, int> & rPair, const Player & rPlayer)
{
	return pushToCoordMap(coordPairToString(rPair), rPlayer);
	/*if (coordinateMap.emplace(coordPairToString(rPair), rPlayer).second)
		return true;*/
	/*coordinateMap[coordPairToString(rPair)] = rPlayer;

	if(coordinateMap[])

	cout << "Pushing to the coordinate map failed." << endl;
	return false;*/
}

bool Board::pushToCoordMap(const int x, const int y, const Player & rPlayer)
{
	pair<int, int> newCoordPair(x, y);

	return pushToCoordMap(newCoordPair, rPlayer);
}

bool Board::pushToIdMap(const unsigned int id, const Player & rPlayer)
{
	/*if (idMap.emplace(id, rPlayer).second)
		return true;*/
	idMap[id] = rPlayer;

	if (idMap[id].getID() == rPlayer.getID())
		return true;

	cout << "Pushing to ID map failed." << endl;
	return false;
}

bool Board::validateCoords(pair<int, int> & rCoords)
{
	bool success = true;

	if (rCoords.first < 1 || rCoords.first > m || rCoords.second < 1 || rCoords.second > m)
	{
		success = false;
		cout << "Coordinates out of bounds." << endl;
	}

	if (coordinateMap.count(coordPairToString(rCoords)))
	{
		success = false;
		cout << "XY coordinate occupied." << endl;
	}

	return success;
}

bool Board::validateId(int id)
{
	bool success = true;

	if (idMap.count(id))
	{
		success = false;
		cout << "A player with the intended ID already exists." << endl;
	}

	return success;
}

bool Board::validateNumPlayers()
{
	return n < m;
}

bool Board::validateBounds(pair<int, int> & rCoords)
{
	return rCoords.first >= 1 && rCoords.first <= m && rCoords.second >= 1 && rCoords.second <= m;
}

bool Board::validateMove(const int id, const pair<int, int> & rCoords)
{
	if (idMap[id].getCoords().first == rCoords.first || idMap[id].getCoords().second == rCoords.second ||
		abs(rCoords.first - idMap[id].getCoords().first) == abs(rCoords.second - idMap[id].getCoords().second))
	{
		
		return true;
	}

	cout << "Invalid XY coordinates for a move." << endl;
	return false;
}

bool Board::addPlayer(Player & rPlayer)
{
	bool success = true;

	success = validateCoords(rPlayer.getCoords()) && validateId(rPlayer.getID()) && validateNumPlayers();

	if (!success)
		return false;

	if (pushToCoordMap(rPlayer.getCoords(), rPlayer) && pushToIdMap(rPlayer.getID(), rPlayer))
	{
		n++;
		success = true;
	}

	return success;

	//if (n >= m)
	//{
	//	cout << "Max number of players reached." << endl;
	//	success = false;
	//}

	//if (coordinateMap.count(coordPairToString( rPlayer.getCoords()))) // returns 1 if element exists
	//{
	//	cout << "XY coordinate occupied." << endl;
	//	success = false;
	//}

	//if (idMap.count(rPlayer.getID()))
	//{
	//	cout << "A player with the intended ID already exists." << endl;
	//	success = false;
	//}
}

bool Board::insert(const int id, const int x, const int y)
{
	Player newPlayer(id, x, y);

	return addPlayer(newPlayer);
}

bool Board::remove(const int id)
{
	//Player removedPlayer = idMap[id];
	if (idMap.count(id))
	{
		cout << "Player " << idMap[id].getID() << " at " << coordPairToString(idMap[id].getCoords());
		if (removeFromCoordMap(idMap[id].getCoords()) && removeFromIdMap(id))
		{
			cout << " was removed successfully." << endl;
			--n;
			return true;
		}
		else
		{
			cout << " was not removed." << endl;
			return false;
		}
	}

	cout << "The player was not found." << endl;
	return false;
}

bool Board::removeFromIdMap(const int id)
{
	return idMap.erase(id);
}

bool Board::removeFromCoordMap(const pair<int, int> & rCoords)
{
	return coordinateMap.erase(coordPairToString(rCoords));
}

bool Board::find(const int id)
{
	return idMap.count(id);
}

bool Board::move(const int id, pair<int, int> & rCoords)
{
	if (!validateBounds(rCoords) || !validateMove(id, rCoords))
	{
		return false;
	}

	if (coordinateMap.count(coordPairToString(rCoords)))
	{
		remove(coordinateMap[coordPairToString(rCoords)].getID());
	}

	removeFromCoordMap(idMap[id].getCoords());

	idMap[id].move(rCoords);
	return pushToCoordMap(rCoords, idMap[id]);
	//return insert(id, rCoords.first, rCoords.second);
}

bool Board::move(const int id, const int x, const int y)
{
	pair<int, int> newCoordPair(x, y);
	return move(id, newCoordPair);
}

void Board::printByID()
{
	map<unsigned int, Player> tempMap;
	for (auto const& x : idMap)
	{
		tempMap[x.first] = x.second;
	}

	for (auto const& y : tempMap)
	{
		cout << "id " << y.first << " at position " << coordPairToString(y.second.getCoords()) << endl;
	}
}