#include "stdafx.h"
#include "GameObjectManager.h"
#include "Card.h"

GameObjectManager::GameObjectManager() {}

GameObjectManager::~GameObjectManager()
{
	std::for_each(_gameObjects.begin(), _gameObjects.end(), GameObjectDeallocator());
}

void GameObjectManager::Add(std::string name, VisibleGameObject* gameObject)
{
	_gameObjects.insert(std::pair<std::string, VisibleGameObject*>(name, gameObject));
}

void GameObjectManager::Remove(std::string name)
{
	std::map<std::string, VisibleGameObject*>::const_iterator results = _gameObjects.find(name);

	if (results != _gameObjects.end())
	{
		delete results->second;
		_gameObjects.erase(results);
	}
}

VisibleGameObject* GameObjectManager::Get(std::string name) const
{
	std::map<std::string, VisibleGameObject*>::const_iterator results = _gameObjects.find(name);

	if (results == _gameObjects.end())
		return NULL;

	return results->second;
}

int GameObjectManager::GetObjectCount() const
{
	return _gameObjects.size();
}

void GameObjectManager::DrawAll(sf::RenderWindow& renderWindow)
{
	std::map<std::string, VisibleGameObject*>::const_iterator itr = _gameObjects.begin();

	while (itr != _gameObjects.end())
	{
		itr->second->Draw(renderWindow);
		itr++;
	}
}

VisibleGameObject * GameObjectManager::CheckBoundaries(int x, int y)
{
	std::map<std::string, VisibleGameObject*>::const_iterator itr = _gameObjects.begin();

	while (itr != _gameObjects.end())
	{
		Card* card = static_cast<Card*>(itr->second);

		if (card->CheckBoundaries(x, y))
		{
			return card;
		}
			
		itr++;
	}

	return nullptr;
}