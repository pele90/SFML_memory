#include "stdafx.h"
#include "VictoryScreen.h"

VictoryScreen::VictoryScreen(std::string filename) : Menu(filename)
{
	// Setup clickable areas

	// Play menu item coordinates
	MenuItem playButton;
	playButton.rect.top = 700;
	playButton.rect.left = 200;
	playButton.rect.width = 500;
	playButton.rect.height = 850;
	playButton.action = Restart;

	//Exit menu item coordinates
	MenuItem exitButton;
	exitButton.rect.top = 700;
	exitButton.rect.left = 800;
	exitButton.rect.width = 1100;
	exitButton.rect.height = 850;
	exitButton.action = Exit;

	_menuItems.push_back(playButton);
	_menuItems.push_back(exitButton);

	if (!_font.loadFromFile(COOLVETICA_FONT))
		std::cerr << "Could not load font" << std::endl;
		
	_scoreboard.setFont(_font);
	_winner.setFont(_font);
	
	_winner.setPosition(440.0f, 130.0f);
	_winner.setCharacterSize(48);
	_winner.setFillColor(sf::Color(18, 76, 239, 255));

	_scoreboard.setPosition(450.0f, 220.0f);
	_scoreboard.setCharacterSize(36);
	_scoreboard.setFillColor(sf::Color(18, 76, 239, 255));
		
}

void VictoryScreen::Show(sf::RenderWindow & window)
{
	window.draw(_sprite);
	window.draw(_winner);
	window.draw(_scoreboard);
	window.display();
}

bool compareFunction(Player* left, Player* right)
{
	return left->GetScore() > right->GetScore();
}

void VictoryScreen::SetScorebord(std::vector<Player*> players)
{
	std::string scoreText, winnerText;

	std::sort(players.begin(), players.end(), compareFunction);

	winnerText.append("The winner is " + players.at(0)->GetName());

	for (auto& player : players)
	{
		scoreText.append(player->GetName() + " \t\t\t " + std::to_string(player->GetScore()) + "\n\n");
	}

	_winner.setString(winnerText);
	_scoreboard.setString(scoreText);
}
