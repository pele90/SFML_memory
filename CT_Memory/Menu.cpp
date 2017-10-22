#include "stdafx.h"
#include "Menu.h"

Menu::Menu(std::string filename) : Screen(filename)
{
}

Menu::MenuResult Menu::Update(sf::RenderWindow& window)
{
	sf::Event menuEvent;

	while (true)
	{
		while (window.pollEvent(menuEvent))
		{
			if (menuEvent.type == sf::Event::MouseButtonPressed)
			{
				return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
			}
			if (menuEvent.type == sf::Event::Closed)
			{
				return MenuResult::Exit;
			}
		}
	}
}

Menu::MenuResult Menu::HandleClick(int x, int y)
{
	std::list<MenuItem>::iterator it;

	for (it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		sf::Rect<int> menuItemRect = (*it).rect;
		if (menuItemRect.height > y
			&& menuItemRect.top < y
			&& menuItemRect.width > x
			&& menuItemRect.left < x)
		{
			return (*it).action;
		}
	}

	return MenuResult::Nothing;
}