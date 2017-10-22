#include "stdafx.h"
#include "Game.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "NumberOfPlayersMenu.h"
#include "VictoryScreen.h"
#include "Card.h"

void Game::Start(void)
{
	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(1280, 960, 32), "Memory");

	_gameState = Game::ShowingSplash;

	while (!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.close();

}

bool Game::IsExiting()
{
	if (_gameState == Game::Exiting)
		return true;
	else
		return false;
}

void Game::GameLoop()
{
	switch (_gameState)
	{
		case Game::ShowingSplash:
		{
			ShowSplashScreen();
			break;
		}
		case Game::ShowingNumOfPlayersMenu:
		{
			ShowNumOfPlayersMenu();
			break;
		}
		case Game::ShowingMenu:
		{
			ShowMenu();
			break;
		}
		case Game::Playing:
		{
			sf::Event currentEvent;
			while (_mainWindow.pollEvent(currentEvent))
			{
				_mainWindow.clear(sf::Color(0, 0, 0));

				if (_table.GetRemainingPairs() == 0)
				{
					_gameState = Game::ShowingVictoryScreen;
				}
				else
				{
					// Check if 2 cards are waiting to be checked and no card is being flipped
					if (!_table.CardFlipping() && _table.GetSelectedCardsSize() == 2)
						if (_table.CheckIfPair())
						{
							_activePlayer->AddScore();
						}
						else
						{
							IncrementPlayerCounter();
							_activePlayer = _players.at(_playerCounter);
						}

					// Get user input
					if (currentEvent.type == sf::Event::MouseButtonPressed)
					{
						// If no card is being flipped
						if (!_table.CardFlipping())
						{
							// If mouse click position is inside a card start flipping that card
							_table.CheckIfCardIsClicked(currentEvent.mouseButton.x, currentEvent.mouseButton.y);
						}
					}

					// Handle other click events
					if (currentEvent.type == sf::Event::Closed)
					{
						_gameState = Game::Exiting;
					}

					if (currentEvent.type == sf::Event::KeyPressed)
					{
						if (currentEvent.key.code == sf::Keyboard::Escape)
							ShowMenu();
					}
				}
			}

			_table.Draw(_mainWindow);

			_mainWindow.display();

			break;
		}
		case Game::ShowingVictoryScreen:
		{
			ShowVictoryScreen();
			break;
		}
	}

}

void Game::ShowSplashScreen()
{
	SplashScreen splashScreen(SPLASH_SCREEN_TEXTURE);
	splashScreen.Show(_mainWindow);
	if (!splashScreen.Update(_mainWindow))
		_gameState = Game::Exiting;
	else
		_gameState = Game::ShowingNumOfPlayersMenu;
}

void Game::ShowMenu()
{
	MainMenu mainMenu(MAIN_MENU_TEXTURE);
	mainMenu.Show(_mainWindow);
	Menu::MenuResult result = mainMenu.Update(_mainWindow);
	switch (result)
	{
		case MainMenu::Exit:
			_gameState = Game::Exiting;
			break;
		case MainMenu::Play:
			_gameState = Game::Playing;
			break;
	}
}

void Game::ShowNumOfPlayersMenu()
{
	NumberOfPlayersMenu numberOfPlayersMenu(NUMBER_OF_PLAYERS_MENU_TEXTURE);
	numberOfPlayersMenu.Show(_mainWindow);
	Menu::MenuResult result = numberOfPlayersMenu.Update(_mainWindow);
	switch (result)
	{
		case Menu::One:
		{
			_numberOfPlayers = 1;
			_gameState = Game::ShowingMenu;
			break;
		}
		case Menu::Two:
		{
			_numberOfPlayers = 2;
			_gameState = Game::ShowingMenu;
			break;
		}
		case Menu::Three:
		{
			_numberOfPlayers = 3;
			_gameState = Game::ShowingMenu;
			break;
		}
		case Menu::Four:
		{
			_numberOfPlayers = 4;
			_gameState = Game::ShowingMenu;
			break;
		}
		case MainMenu::Exit:
		{
			_gameState = Game::Exiting;
			return;
		}
	}

	if (result != Menu::Nothing)
	{
		for (int i = 0; i < _numberOfPlayers; i++)
		{
			Player* player = new Player("Player " + std::to_string(i + 1));

			std::cout << "Player created with the name: " << player->GetName() << std::endl;

			_players.push_back(player);
		}

		_activePlayer = _players.at(0);
		_table.InitGrid(_mainWindow);
	}
}

void Game::ShowVictoryScreen()
{
	VictoryScreen victoryScreen(VICTORY_SCREEN_TEXTURE);
	victoryScreen.SetScorebord(_players);
	victoryScreen.Show(_mainWindow);
	Menu::MenuResult result = victoryScreen.Update(_mainWindow);
	switch (result)
	{
		case Menu::Restart:
		{
			_gameState = Game::ShowingNumOfPlayersMenu;
			ResetGame();
			break;
		}
		case Menu::Exit:
			_gameState = Game::Exiting;
			break;
	}
}

void Game::IncrementPlayerCounter()
{
	if (++_playerCounter > _numberOfPlayers - 1)
		_playerCounter = 0;
}

void Game::ResetGame()
{
	_table.CleanTable();
	
	// delete all allocated pointers in _player vector
	for (auto& player : _players)
	{
		delete player;
		player = 0; // just in case delete fails
	}

	_players.clear();
	_activePlayer = 0;
}

// A quirk of C++, static member variables need to be instantiated outside of the class
Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
Table Game::_table;
std::vector<Player*> Game::_players;
Player* Game::_activePlayer;
int Game::_numberOfPlayers;
int Game::_playerCounter = 0;
