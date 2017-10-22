#include "stdafx.h"
#include "Player.h"

Player::Player()
{

}

Player::Player(std::string name)
	: _name(name)
{
	_score = 0;
}

Player::~Player() {}

std::string Player::GetName()
{
	return _name;
}

int Player::GetScore()
{
	return _score;
}

void Player::AddScore()
{
	_score++;
}
