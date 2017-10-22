#include "stdafx.h"
#include "MainMenu.h"

MainMenu::MainMenu(std::string filename) : Menu(filename)
{
	// Setup clickable areas

	// Play menu item coordinates
	MenuItem playButton;
	playButton.rect.top = 200;
	playButton.rect.left = 400;
	playButton.rect.width = 900;
	playButton.rect.height = 400;
	playButton.action = Play;

	//Exit menu item coordinates
	MenuItem exitButton;
	exitButton.rect.left = 400;
	exitButton.rect.width = 900;
	exitButton.rect.top = 500;
	exitButton.rect.height = 700;
	exitButton.action = Exit;

	_menuItems.push_back(playButton);
	_menuItems.push_back(exitButton);
}


