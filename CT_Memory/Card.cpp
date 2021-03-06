#include "stdafx.h"
#include "Card.h"

Card::Card(int value, std::string textureFilename)
{
	_backTexture.loadFromFile(CARD_BACK_TEXTURE_GNOME);
	_backSprite.setTexture(_backTexture);
	_frontTexture.loadFromFile(textureFilename);
	_frontSprite.setTexture(_frontTexture);

	// Calculating and setting the origin of all transformations for back and front sprites
	float xOrigin = _backSprite.getLocalBounds().width / 2;
	float yOrigin = _backSprite.getLocalBounds().height / 2;

	_backSprite.setOrigin(xOrigin, yOrigin);
	_frontSprite.setOrigin(xOrigin, yOrigin);

	_cardValue = value;
	_currentTime = sf::Time::Zero;
}

void Card::Draw(sf::RenderWindow& renderWindow, sf::Clock clock)
{
	sf::Time delta = clock.restart();

	// after sleep don't add the big delta value so the card don't teleport
	if (delta.asMilliseconds() > 20) delta = sf::Time::Zero; // 20 is eyeballed value

	if (_cardAction == SHOW)
	{
		if (_currentTime < _spinTime - delta)
			_currentTime += sf::milliseconds(16) + delta; // time of frame is 16 miliseconds
		else {
			_currentTime = _spinTime;
			_cardAction = NOTHING;
		}
	}
	else if (_cardAction == HIDE)
	{
		if (_currentTime > delta)
			_currentTime -= sf::milliseconds(16) + delta; // time of frame is 16 miliseconds
		else {
			_currentTime = sf::Time::Zero;
			_cardAction = NOTHING;
		}
	}

	_frontShown = _currentTime >= _spinTime / 2.f;

	if (_frontShown) {
		float scale = (_currentTime - _halfSpinTime) / _halfSpinTime;

		_frontSprite.setScale(std::sin(scale * PI / 2), 1);
		renderWindow.draw(_frontSprite);
	}
	else {
		float scale = 1.0f - _currentTime / _halfSpinTime;
		
		_backSprite.setScale(std::sin(scale * PI / 2), 1);
		renderWindow.draw(_backSprite);
	}
}

void Card::Flip()
{
	if (_frontShown)
		_cardAction = HIDE;
	else
		_cardAction = SHOW;
}

void Card::SetPosition(float x, float y)
{
	_backSprite.setPosition(x, y);
	_frontSprite.setPosition(x, y);
}

bool Card::CheckBoundaries(int x, int y)
{
	sf::FloatRect cardRect;

	if (!_frontShown)
		cardRect = _backSprite.getGlobalBounds();
	else
		cardRect = _frontSprite.getGlobalBounds();

	return cardRect.contains(x, y);
}

int Card::GetValue()
{
	return _cardValue;
}

CardAction Card::GetCardAction()
{
	return _cardAction;
}

bool Card::IsCardFlipped()
{
	return _frontShown;
}