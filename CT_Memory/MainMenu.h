#pragma once
#include "stdafx.h"
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "Menu.h"


class MainMenu : public Menu
{
public:
	MainMenu(std::string filename);
};
