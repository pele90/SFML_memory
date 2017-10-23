 #include "stdafx.h"
#include "NumberOfPlayersMenu.h"

NumberOfPlayersMenu::NumberOfPlayersMenu(std::string filename) : Menu(filename)
{
	// Setup clickable areas

	// One player menu item coordinates
	MenuItem oneButton;
	oneButton.rect.top = 200;
	oneButton.rect.left = 325;
	oneButton.rect.width = 560;
	oneButton.rect.height = 425;
	oneButton.action = One;

	//Two players menu item coordinates
	MenuItem twoButton;
	twoButton.rect.top = 200;
	twoButton.rect.left = 700;
	twoButton.rect.width = 925;
	twoButton.rect.height = 425;
	twoButton.action = Two;

	// Three player menu item coordinates
	MenuItem threeButton;
	threeButton.rect.top = 470;
	threeButton.rect.left = 325;
	threeButton.rect.width = 560;
	threeButton.rect.height = 705;
	threeButton.action = Three;

	//Four players menu item coordinates
	MenuItem fourButton;
	fourButton.rect.top = 470;
	fourButton.rect.left = 700;
	fourButton.rect.width = 925;
	fourButton.rect.height = 705;
	fourButton.action = Four;

	_menuItems.push_back(oneButton);
	_menuItems.push_back(twoButton);
	_menuItems.push_back(threeButton);
	_menuItems.push_back(fourButton);
}

