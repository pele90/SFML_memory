#pragma once
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "Table.h"
#include "Player.h"
#include "GUI.h"

#define CARDS_DELAY_TIME 1 // time to wait before turning the selected cards face down

// This class can be singleton but being static makes it cleaner, no other reason
class Game {

public:
	static void Start();

private:
	static bool IsExiting();
	static void GameLoop();

	static void ShowSplashScreen();
	static void ShowMenu();
	static void ShowNumOfPlayersMenu();
	static void ShowVictoryScreen();
	static void IncrementPlayerCounter();
	static void ResetGame();

	enum GameState { 
		Uninitialized,
		ShowingSplash,
		ShowingNumOfPlayersMenu,
		ShowingMenu,
		Playing,
		Exiting,
		ShowingVictoryScreen 
	};

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;
	static Table _table;
	static std::vector<Player*> _players;
	static Player* _activePlayer;
	static int _numberOfPlayers;
	static int _playerCounter;
	static GUI _gui;
	static sf::Clock _clock;
	static float _fps;
	static sf::Music _ambientMusic;
	static sf::SoundBuffer _buzzerSoundBuffer;
	static sf::SoundBuffer _correctSoundBuffer;
	static sf::Sound _buzzerSound;
	static sf::Sound _correctSound;
};
