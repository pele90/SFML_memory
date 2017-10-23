#include "stdafx.h"
#include "GUI.h"

GUI::GUI() {}

GUI::~GUI() {}

void GUI::Setup(sf::RenderWindow& window, std::vector<Player*> players)
{
	if (!_font.loadFromFile(COOLVETICA_FONT))
		std::cerr << "Could not load font" << std::endl;

	SetupLocations(window);
	int i = 0;

	for (auto& player : players)
	{
		sf::Text playerName;
		playerName.setFont(_font);
		playerName.setCharacterSize(52);
		playerName.setFillColor(sf::Color(0, 0, 0, 255));
		playerName.setString(player->GetName());
		playerName.setPosition(_placements.at(i)._position.x, _placements.at(i)._position.y);
		playerName.setRotation(_placements.at(i)._angle);

		_playerNames.push_back(playerName);

		++i;
	}
}

void GUI::Draw(sf::RenderWindow & window)
{
	for (auto& name : _playerNames)
	{
		window.draw(name);
	}
}

void GUI::SetupLocations(sf::RenderWindow& window)
{
	int halfWidth = window.getSize().x / 2;
	int halfHeight = window.getSize().y / 2;

	sf::Vector2u locationDown;
	locationDown.x = halfWidth - 78;
	locationDown.y = window.getSize().y - 85;
	Placement placementDown(locationDown, 0);
	_placements.push_back(placementDown);

	sf::Vector2u locationUp;
	locationUp.x = halfWidth - 78;
	locationUp.y = 15;
	Placement placementUp(locationUp, 0);
	_placements.push_back(placementUp);

	sf::Vector2u locationLeft;
	locationLeft.x = 24;
	locationLeft.y = halfHeight + 78;
	Placement placementLeft(locationLeft, -90);
	_placements.push_back(placementLeft);

	sf::Vector2u locationRight;
	locationRight.x = window.getSize().x - 24;
	locationRight.y = halfHeight - 78;
	Placement placementRight(locationRight, 90);
	_placements.push_back(placementRight);

}

void GUI::SetActivePlayerColor(int i)
{
	_playerNames.at(i).setFillColor(sf::Color(255, 215, 0));
}

void GUI::SetDeactivePlayerColor(int i)
{
	_playerNames.at(i).setFillColor(sf::Color::Black);
}
