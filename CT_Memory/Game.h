#pragma once
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "PlayerPaddle.h"
#include "GameObjectManager.h"
#include "Table.h"

// This class can be singleton but being static makes it cleaner, no other reason
class Game {

public:

	static void Start();

private:
	static bool IsExiting();
	static void GameLoop();

	static void ShowSplashScreen();
	static void ShowMenu();

	enum GameState { Uninitialized, ShowingSplash, Paused, ShowingMenu, Playing, Exiting };

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;
	static Table _table;
	static GameObjectManager _gameObjectManager;
};
