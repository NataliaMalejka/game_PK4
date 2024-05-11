#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <time.h>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>


class Player
{
private:
	sf::Texture texture;
	sf::Sprite sprite;

	sf::Vector2f velocity;
	sf::Vector2f velocityMax;
	float velocityMin;
	float gravity;
	float acceleration;
	float drag;

public:
	Player();
	virtual ~Player();

	const sf::Vector2f getPosition() const;
	void setPosition(const float x, const float y);
	const sf::FloatRect getGlobalBounds() const;

	const sf::Vector2f getVelocity() const;

	void updateMovement();
	void move(const float dir_x, const float dir_y);
	void updatePhysics();
	void jump();
	bool canJump;

	void update();

	void render(sf::RenderTarget* target);

};

