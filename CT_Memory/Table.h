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
	int GetRandomNumberBeetween(int from, int to);
	bool CardFlipping();
	void GenerateGridSize(int &row, int &column);
	int GetSelectedCardsSize();
	int GetRemainingPairs();

private:
	bool IsPair();

private:
	sf::Texture _texture;
	sf::Sprite _sprite;

	int _rows;
	int _columns;

	std::vector<Card*> _cards;
	std::vector<Card*> _selectedCards;
	int _remainingPairs;

};
