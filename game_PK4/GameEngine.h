#pragma once


#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "Player.h"
#include "Map.h"

class GameEngine
{
private:
	sf::RenderWindow* window;
	sf::Font font;
	sf::Text gameText;
	sf::Text startText;
	sf::Text exitText;	
	sf::CircleShape pointer;

	std::vector<Map*> maps;
	unsigned int mapNumer;
	std::vector<std::string> imageMapNumer;

	Player* player;

	sf::View* view;

	bool startMenu;

public:
	bool newMap;

	GameEngine();
	virtual ~GameEngine();

	void start();
	void loadMap();
	void run();
	void isEvent();
	void closeWindow();

	void update();
	void updateView();
	void updateStart();

	void render();
	void renderStart();
};

#endif