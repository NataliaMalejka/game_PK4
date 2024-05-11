#pragma once
#include "Player.h"
#include "Brick.h"

class Map
{
private:
	sf::Image image;
	std::vector<Brick*> bricks;
	sf::Vector2f playerPosition;

public:

	void readMap();
	Map(const std::string& fileName);
	virtual ~Map();

	std::vector<Brick*> getBricks();
	sf::Vector2f getPlayerPosition();

	void render(sf::RenderTarget* target);
};

