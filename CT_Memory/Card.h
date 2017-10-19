#pragma once
#include "VisibleGameObject.h"

class Card : public VisibleGameObject
{
public:
	Card(int value, std::string textureFilename);
	~Card();

	void Flip();
	void Draw(sf::RenderWindow& renderWindow);
	bool CheckBoundaries(int x, int z);

	void SetPosition(int x, int y);

	enum CardAction { NOTHING, SHOW, HIDE};

private:
	int _cardValue;
	sf::Texture _backTexture;
	sf::Sprite _backFace;
	sf::Texture _frontTexture;
	sf::Sprite _frontFace;

	bool _frontShown = false;
	sf::Time _spinTime = sf::seconds(1);
	sf::Time halfSpinTime = _spinTime / 2.f;
	const float _pi = std::acos(-1);
	CardAction _cardAction = NOTHING;
	sf::Clock _clock;
	sf::Time _currentTime = sf::Time::Zero;
	sf::Time _delta;
};
