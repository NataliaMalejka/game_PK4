#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

#include <mutex>
#include <iostream>
#include <cmath>
#include <chrono>

class Bullet
{
protected:
	sf::Texture texture;
	sf::Sprite sprite;
	float direction;

	std::mutex mutex;

public:
	Bullet();
	Bullet(const float& x, const float& y, const float& dir);
	~Bullet();

	const sf::FloatRect& getGlobalBounds() const;

	void update();
	void updateBossBullet();
	void render(sf::RenderTarget* target);
};

