#include "stdafx.h"
#include "Card.h"

Card::Card(int value, std::string textureFilename)
{
	_backTexture.loadFromFile(CARD_BACK_TEXTURE_GNOME);
	_backFace.setTexture(_backTexture);
	_frontTexture.loadFromFile(textureFilename);
	_frontFace.setTexture(_frontTexture);

	float xOrigin = _backFace.getLocalBounds().width / 2;
	float yOrigin = _backFace.getLocalBounds().height / 2;

	_backFace.setOrigin(xOrigin, yOrigin);
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
		float scale = (_currentTime - _halfSpinTime) / _halfSpinTime;

		_frontFace.setScale(std::sin(scale * PI / 2), 1);
		renderWindow.draw(_frontFace);
	}
	else {
		float scale = 1.f - _currentTime / _halfSpinTime;
		_backFace.setScale(std::sin(scale * PI / 2), 1);
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