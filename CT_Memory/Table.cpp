#include "stdafx.h"
#include "Table.h"

Table::Table()
{
	_texture.loadFromFile(TABLE_TEXTURE);

	_sprite.setTexture(_texture);

	// Initialize random seed
	srand(time(NULL));
}

Table::~Table() {}

void Table::InitGrid(sf::RenderWindow& window)
{
	size_t index = 0;

	GenerateGridSize(_rows, _columns);

	_remainingPairs = (_rows * _columns) / 2;

	std::vector<Card*> availableCards;

	// Create pairs of cards
	for (int i = 0; i < _remainingPairs; i++)
	{
		availableCards.push_back(new Card(i, CARD_FRONT_TEXTURE));
		availableCards.push_back(new Card(i, CARD_FRONT_TEXTURE));
	}

	size_t xOffset = window.getSize().x / (_columns + 1);
	size_t yOffset = window.getSize().y / (_rows + 1);


	for (size_t row = 1; row <= _rows; row++)
	{
		for (size_t column = 1; column <= _columns; column++)
		{
			index = GetRandomNumberBeetween(0, availableCards.size() - 1);

			std::cout << "Card created with value: " << availableCards.at(index)->GetValue() << std::endl;

			// Set position
			availableCards.at(index)->SetPosition(column * xOffset, row * yOffset);

			// Add to list of cards
			_cards.push_back(availableCards.at(index));

			availableCards.erase(availableCards.begin() + index);
		}
	}
}

void Table::Draw(sf::RenderWindow& window)
{
	window.draw(_sprite);

	for (auto& card : _cards)
	{
		card->Draw(window);
	}

	/*for (std::vector<Card*>::iterator iter = _cards.begin(); iter != _cards.end(); iter++)
	{
		(*iter)->Draw(window);
	}*/
}

// Check if any card is clicked, if true return pointer to that card
void Table::CheckIfCardIsClicked(int x, int y)
{
	//for (std::vector<Card*>::iterator iter = _cards.begin(); iter != _cards.end(); iter++)
	//{
	//	// Check if any of the card bounds contains x and y;
	//	if ((*iter)->CheckBoundaries(x, y))
	//	{
	//		if (!(*iter)->IsCardFlipped())
	//		{
	//			(*iter)->Flip();
	//			_selectedCards.push_back((*iter));
	//		}
	//	}
	//}

	for (auto& card : _cards)
	{
		if (card->CheckBoundaries(x, y))
		{
			if (!card->IsCardFlipped())
			{
				card->Flip();
				_selectedCards.push_back(card);
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
		for (auto& card : _selectedCards)
		{
			card->Flip();
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
size_t Table::GetRandomNumberBeetween(size_t fromValue, size_t toValue)
{
	// add 1 to toValue to include the given toValue
	size_t number = rand() % (toValue + 1);

	if (number < fromValue)
		number = fromValue;

	return number;
}

bool Table::CardFlipping()
{
	for (auto& card : _cards)
	{
		if (card->GetCardAction() == CardAction::SHOW || card->GetCardAction() == CardAction::HIDE)
			return true;
	}

	/*for (std::vector<Card*>::iterator iter = _cards.begin(); iter != _cards.end(); iter++)
	{
		if ((*iter)->GetCardAction() == CardAction::SHOW || (*iter)->GetCardAction() == CardAction::HIDE)
			return true;
	}*/

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