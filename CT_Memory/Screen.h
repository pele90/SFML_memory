#pragma once

class Screen
{
public:
	Screen(std::string filename);
	virtual void Show(sf::RenderWindow& window);
	
protected:
	sf::Texture _texture;
	sf::Sprite _sprite; 
};