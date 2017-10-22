#include "stdafx.h"
#include "Card.h"

Card::Card(int value, std::string textureFilename)
{
	_backTexture.loadFromFile(CARD_BACK_TEXTURE_GNOME);
	_backFace.setTexture(_backTexture);

	float xOrigin = _backFace.getLocalBounds().width / 2;
	float yOrigin = _backFace.getLocalBounds().height / 2;

	_backFace.setOrigin(xOrigin, yOrigin);
	_frontTexture.loadFromFile(textureFilename);
	_frontFace.setTexture(_frontTexture);
	_frontFace.setOrigin(xOrigin, yOrigin);
	_cardValue = value;
	_currentTime = sf::Time::Zero;
}

Card::~Card() {}

void Card::Draw(sf::RenderWindow& renderWindow)
{
	
	sf::Time delta = _clock.restart();
	if (_cardAction == SHOW)
	{
		if (_currentTime < _spinTime - delta)
			_currentTime += delta;
		else {
			_currentTime = _spinTime;
			_cardAction = NOTHING;
		}
	}
	else if (_cardAction == HIDE)
	{
		if (_currentTime > delta)
			_currentTime -= delta;
		else {
			_currentTime = sf::Time::Zero;
			_cardAction = NOTHING;
		}
	}

	_frontShown = _currentTime >= _spinTime / 2.f;

	if (_frontShown) {
		// Just scale the sprite based on time:
		float scale = (_currentTime - halfSpinTime) / halfSpinTime;

		// The upscaling is really optional
		_frontFace.setScale(std::sin(scale * _pi / 2), 1);
		renderWindow.draw(_frontFace);
	}
	else {
		// Same here
		float scale = 1.f - _currentTime / halfSpinTime;
		_backFace.setScale(std::sin(scale * _pi / 2), 1);
		renderWindow.draw(_backFace);
	}
}

void Card::Flip()
{
	if (_frontShown)
		_cardAction = HIDE;
	else
		_cardAction = SHOW;
}

void Card::SetPosition(int x, int y)
{
	_backFace.setPosition(x, y);
	_frontFace.setPosition(x, y);
}

bool Card::CheckBoundaries(int x, int y)
{
	sf::FloatRect cardRect;

	if(!_frontShown)
		cardRect = _backFace.getGlobalBounds();
	else
		cardRect = _frontFace.getGlobalBounds();

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