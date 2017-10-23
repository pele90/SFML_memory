#pragma once

class Screen
{
public:
	Screen(std::string filename);
	virtual void Show(sf::RenderWindow& window);
	
protected:
	sf::Texture _backgroundTexture;
	sf::Sprite _backgroundSprite; 
};