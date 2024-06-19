#include "BossBullet.h"

BossBullet::BossBullet(const float& x, const float& y, const float& dir)
{
	if (!texture.loadFromFile("images/bullet.png"))
	{
		std::cout << "ERROR::BOSSBULLET::BOSSBULLET" << std::endl;
	}

	sprite.setTexture(texture);
	sprite.setColor(sf::Color(255, 0, 0));

	if (dir < 0)
	{
		sprite.setPosition(x + 32, y);
	}
	else
		sprite.setPosition(x, y);

	sprite.setScale(dir, 1);

	direction = dir;

	damage = 3;

	startPosition = sprite.getPosition();
	time = 0.f;
	frequency = 2.f;
	amplitude = 40.f;
}

BossBullet::~BossBullet()
{

}

const int& BossBullet::getDamage() const
{
	return damage;
}

void BossBullet::update()
{
	float deltaTime = 1.f / 60.f;
	time += deltaTime;

	sprite.setPosition(startPosition.x + 90.f * direction * time, startPosition.y + amplitude * sinf(frequency * time));
}


