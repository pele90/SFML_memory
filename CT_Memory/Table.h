#pragma once
#include "Card.h"

#define MIN_ROWS 3
#define MAX_ROWS 4
#define MIN_COLUMNS 2
#define MAX_COLUMNS 5

class Table
{
public:
	Table();
	~Table();

	void InitGrid(sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	void CheckIfCardIsClicked(int x, int y);
	bool CheckIfPair();
	size_t GetRandomNumberBeetween(size_t from, size_t to);
	bool CardFlipping();
	void GenerateGridSize(size_t &row, size_t &column);
	size_t GetSelectedCardsSize();
	size_t GetRemainingPairs();
	void CleanTable();

private:
	bool IsPair();

private:
	sf::Texture _texture;
	sf::Sprite _sprite;
	size_t _rows;
	size_t _columns;
	std::vector<Card*> _cards;
	std::vector<Card*> _selectedCards;
	size_t _remainingPairs;
};
