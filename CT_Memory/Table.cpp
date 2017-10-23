#include "stdafx.h"
#include "Table.h"

Table::Table()
{
	_backgroundTexture.loadFromFile(TABLE_TEXTURE);
	_backgroundSprite.setTexture(_backgroundTexture);

	// Initialize random seed
	srand(time(NULL));
}

void Table::InitGrid(sf::RenderWindow& window)
{
	size_t index = 0;

	GenerateGridSize(_rows, _columns);

	_remainingPairs = (_rows * _columns) / 2;


	// First create all available cards
	std::vector<Card*> availableCards;

	// Create pairs of cards and store them in container
	for (int i = 0; i < _remainingPairs; i++)
	{
		availableCards.push_back(new Card(i, CARD_FRONT_TEXTURE + std::to_string(i) + ".png"));
		availableCards.push_back(new Card(i, CARD_FRONT_TEXTURE + std::to_string(i) + ".png"));
	}

	// Offset to move card from the start of the screen
	size_t xOffset = window.getSize().x / (_columns + 1);
	size_t yOffset = window.getSize().y / (_rows + 1);


	for (size_t row = 1; row <= _rows; row++)
	{
		for (size_t column = 1; column <= _columns; column++)
		{
			index = GetRandomNumberBeetween(0, availableCards.size() - 1);

			// Set card position
			availableCards.at(index)->SetPosition(column * xOffset, row * yOffset);

			// Add to list of cards
			_cards.push_back(availableCards.at(index));

			// Remove selected card from <availableCards> container
			// and decrease the size of the containter
			availableCards.erase(availableCards.begin() + index);
		}
	}
}

void Table::Draw(sf::RenderWindow& window)
{
	window.draw(_backgroundSprite);

	for (auto& card : _cards)
	{
		card->Draw(window);
	}
}

// Check if any card is clicked, if true return pointer to that card
void Table::CheckIfCardIsClicked(int x, int y)
{
	for (auto& card : _cards)
	{
		if (card->CheckBoundaries(x, y))
		{
			// Check if card is not flipped, otherwise the card cannot be faced down on click
			if (!card->IsCardFlipped())
			{
				card->Flip();
				_selectedCards.push_back(card);
			}
		}
	}
}

bool Table::CheckSelectedCards()
{
	if (IsPair())
	{
		_remainingPairs--;
		_selectedCards.clear();
		return true;
	}
	else
	{
		for (auto& card : _selectedCards)
		{
			card->Flip();
		}

		_selectedCards.clear();
	}

	return false;
}

// Check if the cards in the <selectedCards> containter have the same value
bool Table::IsPair()
{
	// Compare two cards from _selectedCards vector by their internal value
	return _selectedCards.at(0)->GetValue() == _selectedCards.at(1)->GetValue();
}

// Return random int value between fromValue to toValue; toValue included.
size_t Table::GetRandomNumberBeetween(size_t fromValue, size_t toValue)
{
	// add 1 to toValue to include the given toValue
	size_t number = rand() % (toValue + 1);

	if (number < fromValue)
		number = fromValue;

	return number;
}

// Check if any card is in SHOWING or HIDING stage
bool Table::CardIsFlipping()
{
	for (auto& card : _cards)
	{
		if (card->GetCardAction() == CardAction::SHOW || card->GetCardAction() == CardAction::HIDE)
			return true;
	}

	return false;
}

void Table::GenerateGridSize(size_t & rows, size_t & columns)
{
	size_t gridSize = -1;

	while (gridSize % 2 != 0)
	{
		rows = GetRandomNumberBeetween(MIN_ROWS, MAX_ROWS);
		columns = GetRandomNumberBeetween(MIN_COLUMNS, MAX_COLUMNS);

		gridSize = rows * columns;
	}
}

size_t Table::GetSelectedCardsSize()
{
	return _selectedCards.size();
}

size_t Table::GetRemainingPairs()
{
	return _remainingPairs;
}

void Table::CleanTable()
{
	// delete all allocated pointers from _cards vector
	for (auto& card : _cards)
	{
		delete card;
		card = 0; // just in case delete fails
	}

	_cards.clear();
}