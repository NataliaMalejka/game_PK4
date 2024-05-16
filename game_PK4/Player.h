#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <time.h>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

#include "Map.h"

class Map;

enum PLAYER_ANIMATION_STATES { IDLE = 0, MOVING_LEFT, MOVING_RIGHT, JUMPING, FALLING };

class Player
{
private:
	sf::Texture texture;
	sf::Sprite sprite;

	short animState;
	sf::IntRect currentFrame;
	sf::Clock animationTimer;

	sf::Vector2f velocity;

	sf::Vector2f vel;

public:
	Player();
	virtual ~Player();

	const sf::Vector2f getPosition() const;
	void setPosition(const float x, const float y);
	const sf::FloatRect getGlobalBounds() const;

	const sf::Vector2f getVelocity() const;

	void updateMovement(Map* map, bool& newMap);
	void move(const float dir_x, const float dir_y);
	bool canJump;

	void updateAnimations();
	void update(Map* map, bool& newMap);

	void render(sf::RenderTarget* target);

};

#endif