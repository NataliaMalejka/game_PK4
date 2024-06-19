#include "Brick.h"

Brick::Brick(const float& x, const float& y)
{
	if (!texture.loadFromFile("images/Brick.png"))
	{
		std::cout << "ERROR::BRICK::BRICK" << std::endl;
	}

	sprite.setTexture(texture);
	
	sprite.setPosition((float)x * texture.getSize().x, (float)y * texture.getSize().y);
}

void Brick::isIntersectsX(sf::Sprite& sprite, sf::Vector2f& velocity, bool& newMap, sf::Vector2f& beforeJump)
{
	sprite.move(-velocity.x, 0.f);
}

void Brick::isIntersectsY(sf::Sprite& sprite, sf::Vector2f& velocity, bool& newMap, bool& canJump, sf::Vector2f& beforeJump)
{
	if (velocity.y > 0.f)
	{
		canJump = true;
		beforeJump = getPositionBlock();
	}

	sprite.move(0.f, -velocity.y);
	velocity.y = 0.f;
}
