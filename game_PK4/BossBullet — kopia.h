#pragma once
#include "Bullet.h"

class Bullet;

class BossBullet : public Bullet
{
private:
	int damage;
	sf::Vector2f startPosition;
	float time;
	float frequency;
	float amplitude;

public:
	BossBullet(const float& x, const float& y, const float& dir);
	~BossBullet();

	const int& getDamage() const;
	void update();
};

