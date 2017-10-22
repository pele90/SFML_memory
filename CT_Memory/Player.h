#pragma once

class Player
{
public:
	Player();
	Player(std::string name);
	~Player();

	std::string GetName();
	int GetScore();
	void AddScore();

private:
	std::string _name;
	int _score; // number of pair guessed
};