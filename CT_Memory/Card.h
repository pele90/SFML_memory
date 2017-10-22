#pragma once

#define SPIN_TIME 0.5
#define PI 3.14159265358979323846

enum CardAction { NOTHING, SHOW, HIDE };

class Card
{
public:
	Card(int value, std::string textureFilename);
	~Card();

	void Flip();
	void Draw(sf::RenderWindow& renderWindow);
	bool CheckBoundaries(int x, int z);

	void SetPosition(int x, int y);
	int GetValue();
	CardAction GetCardAction();
	bool IsCardFlipped();

private:
	int _cardValue;
	sf::Texture _backTexture;
	sf::Sprite _backFace;
	sf::Texture _frontTexture;
	sf::Sprite _frontFace;

	bool _frontShown = false;
	sf::Time _spinTime = sf::seconds(SPIN_TIME);
	sf::Time _halfSpinTime = _spinTime / 2.f;
	CardAction _cardAction = NOTHING;
	sf::Clock _clock;
	sf::Time _currentTime;
	
};
