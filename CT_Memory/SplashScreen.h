#pragma once
#include "Screen.h"

class SplashScreen : public Screen
{
public:
	SplashScreen(std::string filename);
	bool Update(sf::RenderWindow& window);
};
