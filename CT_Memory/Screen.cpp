#include "stdafx.h"
#include "Screen.h"

Screen::Screen(std::string filename)
{
	if (!_texture.loadFromFile(filename))
		std::cerr << "Cannot load texture from: " << filename << std::endl;

	_sprite.setTexture(_texture);
}

void Screen::Show(sf::RenderWindow& window)
{
	window.draw(_sprite);
	window.display();
}