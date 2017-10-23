#include "stdafx.h"
#include "Screen.h"

Screen::Screen(std::string filename)
{
	if (!_backgroundTexture.loadFromFile(filename))
		std::cerr << "Cannot load texture from: " << filename << std::endl;

	_backgroundSprite.setTexture(_backgroundTexture);
}

void Screen::Show(sf::RenderWindow& window)
{
	window.draw(_backgroundSprite);
	window.display();
}