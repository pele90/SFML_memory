#include "stdafx.h"
#include "VisibleGameObject.h"

VisibleGameObject::VisibleGameObject() : _isLoaded(false){}

VisibleGameObject::~VisibleGameObject(){}

void VisibleGameObject::Load(std::string filename)
{
	if (_texture.loadFromFile(filename) == false)
	{
		_fileName = "";
		_isLoaded = false;
	}
	else
	{
		_fileName = filename;
		_sprite.setTexture(_texture);
		_isLoaded = true;
	}
}

void VisibleGameObject::Draw(sf::RenderWindow& renderWindow)
{
	if (_isLoaded)
		renderWindow.draw(_sprite);
}

void VisibleGameObject::SetPosition(float x, float y)
{
	if (_isLoaded)
		_sprite.setPosition(x, y);
}