#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <ranges>

#include "BossBullet.h"

class Enemy
{
protected:
	int MaxHp;
	int Hp;
	int Cp;

	sf::Sprite sprite;
	sf::Texture texture;

	sf::Vector2f velocity;
	sf::Clock moveTimer;
	sf::Clock attackTimer;
	sf::Clock gotDamageTimer;

	virtual void updateMove(const sf::Vector2f& playerPosition) = 0;

public:

	virtual ~Enemy() = default;

	const int& getCp() const;
	const int& getHp() const;

	void gotDamage(const int& damage);
	void stepBack();

	const sf::Vector2f& getPositionEnemy() const;
	const sf::FloatRect& getGlobalBounds();

	const bool getAttackTimer() const;
	const bool getGotDamageTimer() const;

	void setAttackTimer();
	void setGotDamageTimer();

	virtual void update(const sf::Vector2f& playerPosition, std::vector<BossBullet*>& bossBullets, std::vector<Enemy*>& enemies) = 0;
	void render(sf::RenderTarget* target);
};

