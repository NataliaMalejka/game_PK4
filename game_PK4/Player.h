#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <time.h>
#include <memory>
#include <thread>
#include <mutex>
#include <future>
#include <filesystem>
#include <cmath>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

#include "Map.h"

#include "Block.h"
#include "Brick.h"
#include "Teleport.h"
#include "Spikes.h"

class Map;

enum PLAYER_ANIMATION_STATES { IDLE = 0, MOVING_LEFT, MOVING_RIGHT, FIGHTING_1, FIGHTING_1_RUN, USE_SHIELD};

class Player
{
private:
	int MaxHp;
	int Hp;

	int weapon;
	std::vector<bool> isWeapon;
	std::vector<int> weaponDamage;

	float attackCooldown;
	float attackCooldownMax;
	float attackCooldownBullet;

	bool canJump;
	bool useShield;

	sf::Sprite sprite;
	sf::Texture texture;

	short animState;
	sf::IntRect currentFrame;

	sf::Clock animationTimer;
	sf::Clock gotDamageClock;
	sf::Clock attackTimer;

	sf::Music swordSounds;

	sf::Vector2f velocity;
	sf::Vector2f beforeJump;

	void updateMovement(Map* map, bool& newMap);
	void updateAnimState(const sf::Vector2f& vel);
	void move(const float& dir_x, const float& dir_y);

	void updateAnimations();	
	void animations();

	void upedateAttack(float& attackType, const float& value);

public:

	Player();
	virtual ~Player();

	const sf::Vector2f getPosition() const;
	void setPosition(const float& x, const float& y);

	const sf::Vector2f getVelocity() const;
	void setVelocity(const float& x, const float& y);

	const sf::FloatRect getGlobalBounds() const;
	const sf::FloatRect getGlobalBoundsY() const;
	const sf::FloatRect getAttackRect() const;
	const sf::FloatRect getShieldRect() const;

	const bool canAttack();

	const bool canAttackBullet();

	const float& getAttackCooldownBullet() const;

	const bool getAttackTimer() const;

	const bool getIsBullet() const;

	const bool getUseShield() const;

	const int& getWeapon();

	std::vector<bool>& getIsWeapon();

	const std::vector<int>& getWeaponDamage() const;

	void setWeapon(const int& i);

	void gotDamage(const int& damage);

	const int& getHp() const;
	void setHp(const int& hp);
	const int& getMaxHp() const;
	const float& getDirection() const;

	void update(Map* map, bool& newMap);

	void render(sf::RenderTarget* target);
};

#endif