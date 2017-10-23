#pragma once
#include "Screen.h"

class Menu : public Screen
{
public:
	enum MenuResult {
		Nothing,
		Exit,
		Play,
		Restart,
		One,
		Two,
		Three,
		Four
	};

	struct MenuItem
	{
		sf::Rect<int> rect;
		MenuResult action;
	};

	Menu(std::string filename);
	MenuResult Update(sf::RenderWindow& window);

protected:
	MenuResult HandleClick(int x, int y);
	std::list<MenuItem> _menuItems;
};