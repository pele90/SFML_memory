#include "stdafx.h"
#include "GUI.h"

GUI::GUI() {}

void GUI::Setup(sf::RenderWindow& window, std::vector<Player*> players)
{
	if (!_font.loadFromFile(COOLVETICA_FONT))
		std::cerr << "Could not load font" << std::endl;

	SetupLocations(window);

	int index = 0;

	for (auto& player : players)
	{
		sf::Text playerName;
		playerName.setFont(_font);
		playerName.setCharacterSize(52);
		playerName.setFillColor(sf::Color(0, 0, 0, 255));
		playerName.setString(player->GetName());
		playerName.setPosition(_placements.at(index)._position.x,
							   _placements.at(index)._position.y);
		playerName.setRotation(_placements.at(index)._angle);

		_playerNames.push_back(playerName);

		++index;
	}

	_fpsText.setFont(_font);
	_fpsText.setCharacterSize(40);
	_fpsText.setFillColor(sf::Color::White);
	_fpsText.setPosition(10, 10);
}

void GUI::Draw(sf::RenderWindow & window, float fps)
{
	for (auto& name : _playerNames)
	{
		window.draw(name);
	}

#ifdef _DEBUG
	_fpsText.setString("FPS: " + std::to_string(fps));
	window.draw(_fpsText);
#endif // _DEBUG

	
}

void GUI::SetupLocations(sf::RenderWindow& window)
{
	// Manually setup locations on screen for players name

	int halfWidth = window.getSize().x / 2;
	int halfHeight = window.getSize().y / 2;

	sf::Vector2f locationDown;
	locationDown.x = halfWidth - 78.0f;
	locationDown.y = window.getSize().y - 85.0f;
	Placement placementDown(locationDown, 0.0f);
	_placements.push_back(placementDown);

	sf::Vector2f locationUp;
	locationUp.x = halfWidth - 78.0f;
	locationUp.y = 15.0f;
	Placement placementUp(locationUp, 0.0f);
	_placements.push_back(placementUp);

	sf::Vector2f locationLeft;
	locationLeft.x = 24.0f;
	locationLeft.y = halfHeight + 78.0f;
	Placement placementLeft(locationLeft, -90);
	_placements.push_back(placementLeft);

	sf::Vector2f locationRight;
	locationRight.x = window.getSize().x - 24.0f;
	locationRight.y = halfHeight - 78.0f;
	Placement placementRight(locationRight, 90);
	_placements.push_back(placementRight);

}

void GUI::SetActivePlayerColor(int i)
{
	_playerNames.at(i).setFillColor(sf::Color(255, 215, 0));
}

void GUI::SetDefaultPlayerColor(int i)
{
	_playerNames.at(i).setFillColor(sf::Color::Black);
}

void GUI::Reset()
{
	_playerNames.clear();
}