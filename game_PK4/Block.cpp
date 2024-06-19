#include "Block.h"

const sf::Vector2f Block::getPositionBlock() const
{
	return sprite.getPosition();
}

const sf::FloatRect Block::getGlobalBounds() const
{
	return sprite.getGlobalBounds();
}

void Block::render(sf::RenderTarget* target)
{
	target->draw(sprite);
}