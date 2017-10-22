#include "stdafx.h"
#include "Table.h"

Table::Table()
{
	// Initialize random seed
	srand(time(NULL));
}

Table::~Table() {}

void Table::InitGrid(sf::RenderWindow& window)
{
	int index = 0;
	Card* card = nullptr;

	GenerateGridSize(_rows, _columns);

	_remainingPairs = (_rows * _columns) / 2;

	std::vector<Card*> availableCards;

	for (int i = 0; i < _remainingPairs; i++)
	{
		availableCards.push_back(new Card(i, CARD_FRONT_TEXTURE));
		availableCards.push_back(new Card(i, CARD_FRONT_TEXTURE));
	}

	float xOffset = window.getSize().x / (_columns + 1);
	float yOffset = window.getSize().y / (_rows + 1);


	for (int row = 1; row <= _rows; row++)
	{
		for (int column = 1; column <= _columns; column++)
		{
			index = GetRandomNumberBeetween(0, availableCards.size() - 1);

			card = availableCards.at(index);
			std::cout << "Card created with value: " << card->GetValue() << std::endl;

			// Set position
			card->SetPosition(column * xOffset, row * yOffset);

			// Add to list of cards
			_cards.push_back(card);

			availableCards.erase(availableCards.begin() + index);
		}
	}
}

void Table::Draw(sf::RenderWindow& window)
{
	for (std::vector<Card*>::iterator iter = _cards.begin(); iter != _cards.end(); iter++)
	{
		(*iter)->Draw(window);
	}
}

// Check if any card is clicked, if true return pointer to that card
void Table::CheckIfCardIsClicked(int x, int y)
{
	for (std::vector<Card*>::iterator iter = _cards.begin(); iter != _cards.end(); iter++)
	{
		// Check if any of the card bounds contains x and y;
		if ((*iter)->CheckBoundaries(x, y))
		{
			if (!(*iter)->IsCardFlipped())
			{
				(*iter)->Flip();
				_selectedCards.push_back((*iter));
			}
		}
	}
}

bool Table::CheckIfPair()
{
	if (IsPair())
	{
		_remainingPairs--;
		_selectedCards.clear();
		return true;
	}
	else
	{
		for (std::vector<Card*>::iterator iter = _selectedCards.begin(); iter != _selectedCards.end(); iter++)
		{
			(*iter)->Flip();
		}

		_selectedCards.clear();
	}

	return false;
}

bool Table::IsPair()
{
	// Compare two cards from _selectedCards vector by their internal value
	return _selectedCards.at(0)->GetValue() == _selectedCards.at(1)->GetValue();
}

// Return random int value between fromValue to toValue; toValue included.
int Table::GetRandomNumberBeetween(int fromValue, int toValue)
{
	// add 1 to toValue to include the given toValue
	int number = rand() % (toValue + 1);

	if (number < fromValue)
		number = fromValue;

	return number;
}

bool Table::CardFlipping()
{
	for (std::vector<Card*>::iterator iter = _cards.begin(); iter != _cards.end(); iter++)
	{
		if ((*iter)->GetCardAction() == CardAction::SHOW || (*iter)->GetCardAction() == CardAction::HIDE)
			return true;
	}

	return false;
}

void Table::GenerateGridSize(int & rows, int & columns)
{
	int gridSize = -1;

	while (gridSize % 2 != 0)
	{
		rows = GetRandomNumberBeetween(MIN_ROWS, MAX_ROWS);
		columns = GetRandomNumberBeetween(MIN_COLUMNS, MAX_COLUMNS);

		gridSize = rows * columns;
	}
}

int Table::GetSelectedCardsSize()
{
	return _selectedCards.size();
}

int Table::GetRemainingPairs()
{
	return _remainingPairs;
}