#pragma once
#include "Player.h"
#include "Map.h"

class GameEngine
{
private:
	sf::RenderWindow* window;
	std::vector<Map*> maps;
	unsigned int mapNumer;
	std::vector<std::string> imageMapNumer;
	Player* player;


public:
	GameEngine();
	virtual ~GameEngine();

	void start();
	void loadMap();
	void run();
	void isEvent();
	void close();

	void updateCollision();
	void update();

	void render();
};

