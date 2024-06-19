#include "Bullet.h"

Bullet::Bullet()
{
	direction = 1.f;
}

Bullet::Bullet(const float& x, const float& y, const float& dir)
{
	if (!texture.loadFromFile("images/bullet.png"))
	{
		std::cout << "ERROR::BULLET::BULLET" << std::endl;
	}

	sprite.setTexture(texture);

	if (dir < 0)
	{
		sprite.setPosition(x + 16, y);
	}
	else
		sprite.setPosition(x,y);

	sprite.setScale(dir, 1);

	direction = dir;
}

Bullet::~Bullet()
{

}

const sf::FloatRect& Bullet::getGlobalBounds() const
{
	return sprite.getGlobalBounds();
}

void Bullet::update()
{
	mutex.lock();
	sprite.move(2.5f * direction, 0.f);
	mutex.unlock();
}

void Bullet::updateBossBullet()
{

}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(sprite);
}
