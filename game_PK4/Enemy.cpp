#include "Enemy.h"

void Enemy::gotDamage(const int& damage)
{
	Hp -= damage;
	sprite.setColor(sf::Color(255, 0, 0));
}

void Enemy::stepBack()
{
	if (velocity.x < 0)
	{
		sprite.move( 6.f, 0.f);
	}
	if (velocity.x > 0)
	{
		sprite.move(-6.f, 0.f);
	}
	
	moveTimer.restart();
}

const int& Enemy::getCp() const
{
	return Cp;
}

const int& Enemy::getHp() const
{
	return Hp;
}

const sf::Vector2f& Enemy::getPositionEnemy() const
{
	return sprite.getPosition();
}

const sf::FloatRect& Enemy::getGlobalBounds()
{
	return sprite.getGlobalBounds();
}

const bool Enemy::getAttackTimer() const
{
	if (attackTimer.getElapsedTime().asSeconds() > 0.5)
		return true;
	else
		return false;
}

const bool Enemy::getGotDamageTimer() const
{
	if (gotDamageTimer.getElapsedTime().asSeconds() > 0.25f)
		return true;
	else
		return false;
}

void Enemy::setAttackTimer()
{
	attackTimer.restart();
}

void Enemy::setGotDamageTimer()
{
	gotDamageTimer.restart();
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(sprite);
}
