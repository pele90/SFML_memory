#include "stdafx.h"
#include "SplashScreen.h"

SplashScreen::SplashScreen(std::string filename) : Screen(filename) {}

bool SplashScreen::Update(sf::RenderWindow& window)
{
	sf::Event event;
	while (true)
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed
				|| event.type == sf::Event::MouseButtonPressed)
			{
				return true;
			}
			else if(event.type == sf::Event::Closed)
				return false;
		}
	}
}