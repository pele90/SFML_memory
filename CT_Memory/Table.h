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

	void InitGrid(sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window, sf::Clock clock);
	void CleanTable();
	void CheckIfCardIsClicked(int x, int y);
	void GenerateGridSize(size_t &row, size_t &column);
	bool CheckSelectedCards();
	bool CardIsFlipping();
	size_t GetRandomNumberBeetween(size_t from, size_t to);
	size_t GetSelectedCardsSize();
	size_t GetRemainingPairs();
	

private:
	bool IsPair();

private:
	sf::Texture _backgroundTexture;
	sf::Sprite _backgroundSprite;
	size_t _rows;
	size_t _columns;
	std::vector<Card*> _cards;
	std::vector<Card*> _selectedCards;
	size_t _remainingPairs;
};
