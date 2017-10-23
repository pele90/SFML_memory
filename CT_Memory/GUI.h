#pragma once
#include "Player.h"

struct Placement
{
	Placement(sf::Vector2u position, float angle)
		: _position(position), _angle(angle) {}

	sf::Vector2u _position;
	float _angle;
};

class GUI
{
public:
	GUI();

	void Setup(sf::RenderWindow& window, std::vector<Player*> players);
	void Draw(sf::RenderWindow& window);
	void SetActivePlayerColor(int i);
	void SetDefaultPlayerColor(int i);
	void Reset();

private:
	void SetupLocations(sf::RenderWindow& window);

private:
	sf::Font _font;
	std::vector<sf::Text> _playerNames;
	std::vector<Placement> _placements;
};
