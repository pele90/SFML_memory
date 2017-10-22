#include "stdafx.h"
#include "NumberOfPlayersMenu.h"

NumberOfPlayersMenu::NumberOfPlayersMenu(std::string filename) : Menu(filename)
{
	// Setup clickable areas

	// One player menu item coordinates
	MenuItem oneButton;
	oneButton.rect.top = 200;
	oneButton.rect.left = 225;
	oneButton.rect.width = 550;
	oneButton.rect.height = 525;
	oneButton.action = One;

	//Two players menu item coordinates
	MenuItem twoButton;
	twoButton.rect.top = 200;
	twoButton.rect.left = 730;
	twoButton.rect.width = 1060;
	twoButton.rect.height = 525;
	twoButton.action = Two;

	// Three player menu item coordinates
	MenuItem threeButton;
	threeButton.rect.top = 600;
	threeButton.rect.left = 225;
	threeButton.rect.width = 550;
	threeButton.rect.height = 920;
	threeButton.action = Three;

	//Four players menu item coordinates
	MenuItem fourButton;
	fourButton.rect.top = 600;
	fourButton.rect.left = 730;
	fourButton.rect.width = 1060;
	fourButton.rect.height = 920;
	fourButton.action = Four;

	_menuItems.push_back(oneButton);
	_menuItems.push_back(twoButton);
	_menuItems.push_back(threeButton);
	_menuItems.push_back(fourButton);
}

