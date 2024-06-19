#include "Spikes.h"

Spikes::Spikes(const float& x, const float& y)
{
	if (!texture.loadFromFile("images/Kolce.png"))
	{
		std::cout << "ERROR::SPIKES::SPIKES" << std::endl;
	}

	sprite.setTexture(texture);
	sprite.setPosition((float)x * texture.getSize().x, (float)y * texture.getSize().y);
}

void Spikes::isIntersectsX(sf::Sprite& sprite, sf::Vector2f& velocity, bool& newMap, sf::Vector2f& beforeJump)
{
	velocity.x = 0;
	velocity.y = 0;
	sprite.setPosition(beforeJump.x, beforeJump.y - 33.f);
}

void Spikes::isIntersectsY(sf::Sprite& sprite, sf::Vector2f& velocity, bool& newMap, bool& canJump, sf::Vector2f& beforeJump)
{
	velocity.x = 0;
	velocity.y = 0;
	sprite.setPosition(beforeJump.x, beforeJump.y - 33.f);
}