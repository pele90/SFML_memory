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
	// Calculate number of rows and column
	_rows = GetRandomNumberBeetween(MIN_ROWS, MAX_ROWS);
	_columns = GetRandomNumberBeetween(MIN_COLUMNS, MAX_COLUMNS);

	float xOffset = window.getSize().x / (_columns + 1);
	float yOffset = window.getSize().y / (_rows + 1);


	for (int row = 1; row <= _rows; row++)
	{
		for (int column = 1; column <= _columns; column++)
		{
			// Create card
			Card* card = new Card(1, CARD_FRONT_TEXTURE);

			std::cout << "Card created!" << std::endl;

			// Set position
			card->SetPosition(column * xOffset, row * yOffset);

			// Add to list of cards
			_cards.push_back(card);
		}
	}
}

void Table::Draw(sf::RenderWindow& window)
{
	// Draw table sprite

	// Loop through all cards and call their draw method
	for (std::vector<Card*>::iterator iter = _cards.begin(); iter != _cards.end(); iter++)
	{
		(*iter)->Draw(window);
	}
}

Card* Table::CheckIfCardIsClicked(int x, int y)
{
	// Check if any of the card bounds contains x and y;

	for (std::vector<Card*>::iterator iter = _cards.begin(); iter != _cards.end(); iter++)
	{
		if ((*iter)->CheckBoundaries(x, y))
			return (*iter);
	}

	return nullptr;
}

bool Table::IsPair()
{
	// Compare two cards from _selectedCards vector by their internal value
	return false;
}

// Return random int value between fromValue to toValue; toValue included.
int Table::GetRandomNumberBeetween(int fromValue, int toValue)
{
	// add 1 to toValue to include the given toValue
	int number = rand() % (toValue + 1);

	if(number < fromValue)
		number = fromValue;

	return number;
}


