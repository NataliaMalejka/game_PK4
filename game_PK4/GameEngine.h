#pragma once

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "Player.h"
#include "Map.h"
#include "Bullet.h"
#include "BossBullet.h"
#include "Health.h"
#include "Item.h"

class GameEngine
{
private:
	sf::RenderWindow* window;
	sf::Font font;
	sf::Text gameText;
	sf::Text playText;
	sf::Text exitText;	
	sf::Text gameOverText;
	sf::Text winText;
	sf::CircleShape pointer;

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprte;

	sf::Music musicBackground;
	sf::Music soundsItem;
	sf::Music soundsHealth;
	sf::Music soundsBullet;

	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	sf::RectangleShape playerBulletBar;
	sf::RectangleShape playerBulletBarBack;

	std::vector<Map*> maps;

	int mapNumer;
	std::vector<std::string> imageMapNumer;
	bool newMap;

	Player* player;

	sf::View* view;

	std::vector<Enemy*>enemies;

	std::vector<Bullet*> bullets;

	std::vector<BossBullet*> bossBullets;

	std::vector<Health*> health;

	std::vector<Item*> items;

	bool startMenu;
	bool pauseMenu;

	void start();
	void loadMap();
	void isEvent();

	void update();
	void updateContact();
	void updateBars();
	void updateView();
	void updateButton(sf::Text& text);

	void renderBar();
	void render();
	void renderMenu();

public:

	GameEngine();
	virtual ~GameEngine();

	void run();

};

#endif