#include "Teleport.h"

Teleport::Teleport(const float& x, const float& y)
{
	if (!texture.loadFromFile("images/teleport.png"))
	{
		std::cout << "ERROR::TELEPORT::TELEPORT" << std::endl;
	}

	sprite.setTexture(texture);
	sprite.setPosition((float)x * texture.getSize().x, (float)y * texture.getSize().y);
}

void Teleport::isIntersectsX(sf::Sprite& sprite, sf::Vector2f& velocity, bool& newMap, sf::Vector2f& beforeJump)
{
	newMap = true;
}

void Teleport::isIntersectsY(sf::Sprite& sprite, sf::Vector2f& velocity, bool& newMap, bool& canJump, sf::Vector2f& beforeJump)
{
	newMap = true;
}