#pragma once

#ifndef MAP_H
#define MAP_H

#include "Player.h"

#include "Enemy.h"
#include "Ghost.h"
#include "Shadow.h"
#include "Boss.h"
#include "Health.h"
#include "Item.h"

class Block;
class Brick;

class Map
{
private:
	sf::Image image;
	std::vector<Block*> blocks;
	sf::Vector2f playerPosition;

public:
	void readMap(std::vector<Enemy*>& enemies, std::vector<Health*>& health, std::vector<Item*>& items);

	Map(const std::string& fileName);
	virtual ~Map();

	std::vector<Block*> getBlocks();
	sf::Vector2f getPlayerPosition();

	void render(sf::RenderTarget* target);
};

#endif