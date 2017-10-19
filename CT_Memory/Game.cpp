#include "stdafx.h"
#include "Game.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "Card.h"

void Game::Start(void)
{
	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(1024, 768, 32), "Memory");

	// Create all cards randomly

	Card* card = new Card(1, "../data/front.png");
	card->SetPosition(128, 190);
	_gameObjectManager.Add("card", card);

	Card* card2 = new Card(2, "../data/front_1.png");
	card2->SetPosition(256, 190);
	_gameObjectManager.Add("card2", card2);

	Card* card3 = new Card(3, "../data/front_2.png");
	card3->SetPosition(384, 190);
	_gameObjectManager.Add("card3", card3);

	Card* card4 = new Card(4, "../data/front_3.png");
	card4->SetPosition(128, 380);
	_gameObjectManager.Add("card4", card4);

	Card* card5 = new Card(5, "../data/front_4.png");
	card5->SetPosition(256, 380);
	_gameObjectManager.Add("card5", card5);

	Card* card6 = new Card(6, "../data/front_5.png");
	card6->SetPosition(384, 380);
	_gameObjectManager.Add("card6", card6);

	// Create all cards randomly

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
				
				// Get user input
				if (currentEvent.type == sf::Event::MouseButtonPressed)
				{
					Card* card = (Card*) _gameObjectManager.CheckBoundaries(currentEvent.mouseButton.x, currentEvent.mouseButton.y);

					if (card != nullptr)
						card->Flip();
					// check if mouse click position is inside any of the cards
					//return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
				}

				// Check and update objects
				// If mouse click position is inside a card start flipping that card

				// Draw all visible objects
				_gameObjectManager.DrawAll(_mainWindow);

				// Check win condition if card is not flipping

				_mainWindow.display();

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
			break;
		}
	}
}

void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
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

// A quirk of C++, static member variables need to be instantiated outside of the class
Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;
