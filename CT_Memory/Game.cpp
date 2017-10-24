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
	_mainWindow.setFramerateLimit(60);

	if(!_ambientMusic.openFromFile(AMBIENT_MUSIC))
		std::cerr << "Could not load music file" << std::endl;

	if(!_buzzerSoundBuffer.loadFromFile(BUZZER_SOUND))
		std::cerr << "Could not load \"buffer\" sound file" << std::endl;

	if (!_correctSoundBuffer.loadFromFile(CORRECT_SOUND))
		std::cerr << "Could not load \"correct\" sound file" << std::endl;

	_ambientMusic.setLoop(true);

	_buzzerSound.setBuffer(_buzzerSoundBuffer);
	_buzzerSound.setVolume(50); // this sound has 50% lower volume because it's annoying

	_correctSound.setBuffer(_correctSoundBuffer);

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
			sf::Time currentTime = _clock.getElapsedTime();
			_fps = 1.0f / currentTime.asSeconds();

			_clock.restart().asSeconds();

			_mainWindow.clear(sf::Color(0, 0, 0));

			if (_table.GetRemainingPairs() == 0)
			{
				_gameState = Game::ShowingVictoryScreen;
				_gui.SetDefaultPlayerColor(_playerCounter);
			}
			else
			{
				// Check if no card is being flipped 
				// and 2 cards are waiting to be checked i.e. are in the <selectedCards> container
				if (!_table.CardIsFlipping() && _table.GetSelectedCardsSize() == 2)
				{
					// If two cards in the <selectedCards> container have the same value
					if (_table.CheckSelectedCards())
					{
						_correctSound.play();
						_activePlayer->AddScore();
					}
					else
					{
						_buzzerSound.play();

						// time to wait before turning both card faced down
						sf::sleep(sf::seconds(CARDS_DELAY_TIME));

						// Return previously active player's text color to default
						_gui.SetDefaultPlayerColor(_playerCounter);

						IncrementPlayerCounter();

						// Set next player as active
						_activePlayer = _players.at(_playerCounter);

						// Set the new active player's text color to gold
						_gui.SetActivePlayerColor(_playerCounter);
					}
				}

				sf::Event currentEvent;
				while (_mainWindow.pollEvent(currentEvent))
				{
					// Get player's mouse input
					if (currentEvent.type == sf::Event::MouseButtonPressed)
					{
						// If no card is being flipped
						if (!_table.CardIsFlipping())
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

				// Draw table and cards sprites
				_table.Draw(_mainWindow, _clock);

				_gui.Draw(_mainWindow, _fps);

				// SFML method for showing all drawn textures and sprites on screen
				_mainWindow.display();
			}

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
	{
		_gameState = Game::Exiting;
	}
	else
	{
		_gameState = Game::ShowingNumOfPlayersMenu;
		_ambientMusic.play();
	}
}

void Game::ShowMenu()
{
	MainMenu mainMenu(MAIN_MENU_TEXTURE);
	mainMenu.Show(_mainWindow);
	Menu::MenuResult result = mainMenu.Update(_mainWindow);
	switch (result)
	{
		case MainMenu::Exit:
		{
			_gameState = Game::Exiting;
			break;
		}
		case MainMenu::Play:
		{
			_gameState = Game::Playing;
			break;
		}
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
			Player* player = new Player("Player" + std::to_string(i + 2));

			_players.push_back(player);
		}

		_activePlayer = _players.at(0);

		_table.InitGrid(_mainWindow);

		_gui.Setup(_mainWindow, _players);

		_gui.SetActivePlayerColor(_playerCounter);
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

	// delete all allocated pointers in <_players> container
	for (auto& player : _players)
	{
		delete player;
		player = 0; // just in case delete fails
	}

	_players.clear();
	_gui.Reset();
	_activePlayer = 0;
	_playerCounter = 0;
}

// A quirk of C++, static member variables need to be instantiated outside of the class
Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
Table Game::_table;
std::vector<Player*> Game::_players;
Player* Game::_activePlayer;
int Game::_numberOfPlayers;
int Game::_playerCounter = 0;
GUI Game::_gui;
sf::Clock Game::_clock;
float Game::_fps;
sf::Music Game::_ambientMusic;
sf::SoundBuffer Game::_buzzerSoundBuffer;
sf::SoundBuffer Game::_correctSoundBuffer;
sf::Sound Game::_buzzerSound;
sf::Sound Game::_correctSound;