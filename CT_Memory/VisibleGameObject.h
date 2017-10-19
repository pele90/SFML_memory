#pragma once

class VisibleGameObject
{
public:
	VisibleGameObject();
	virtual ~VisibleGameObject();

	virtual void Draw(sf::RenderWindow& window) = 0;

protected:
	bool _isLoaded;
};
