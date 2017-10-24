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
	void SetPosition(float x, float y);
	bool CheckBoundaries(int x, int z);
	void Draw(sf::RenderWindow& renderWindow, sf::Clock clock);

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
	sf::Time _currentTime;
	
};
