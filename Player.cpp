#pragma once
#include "player.h"

Player::Player()
{
	id = 0;
	coords.first = 0;
	coords.second = 0;
}

Player::Player(int newId, pair<int, int> newCoords) : id(newId)
{
	coords = newCoords;
}

Player::Player(Player & rOther)
{
	*this = rOther;
}

Player & Player::operator=(const Player & other)
{
	id = other.id;
	coords.first = other.coords.first;
	coords.second = other.coords.second;

	return *this;
}

Player::Player(int newId, int xCoord, int yCoords) : id(newId)
{
	coords.first = xCoord;
	coords.second = yCoords;
}

//Player::Player(Player & rRhs) : id(rRhs.getID())
//{
//	coords = rRhs.getCoords();
//}

int Player::getID() const
{
	return id;
}

pair<int, int> Player::getCoords() const
{
	return coords;
}

void Player::getCoords(int & rX, int & rY)
{
	rX = coords.first;
	rY = coords.second;
}

void Player::move(pair<int, int>&rNewCoords)
{
	coords = rNewCoords;
}

void Player::move(int x, int y)
{
	coords.first = x;
	coords.second = y;
}