#pragma once

#define SPIN_TIME 1

enum CardAction { NOTHING, SHOW, HIDE };

class Card
{
public:
	Card(int value, std::string textureFilename);

	void Flip();
	int GetValue();
	bool IsCardFlipped();
	CardAction GetCardAction();
	void SetPosition(int x, int y);
	bool CheckBoundaries(int x, int z);
	void Draw(sf::RenderWindow& renderWindow);

private:
	int _cardValue;
	sf::Texture _backTexture;
	sf::Sprite _backSprite;
	sf::Texture _frontTexture;
	sf::Sprite _frontSprite;

	bool _frontShown = false;
	sf::Time _spinTime = sf::seconds(SPIN_TIME);
	sf::Time _halfSpinTime = _spinTime / 2.f;
	CardAction _cardAction = NOTHING;
	sf::Clock _clock;
	sf::Time _currentTime;
	
};
