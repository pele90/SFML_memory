#pragma once
#include "Menu.h"
#include "Player.h"

class VictoryScreen : public Menu
{
public:
	VictoryScreen(std::string filename);
	virtual void Show(sf::RenderWindow& window);

	void SetScorebord(const std::vector<Player*> players);

private:
	sf::Text _scoreboard;
	sf::Font _font;
};