#include "Brick.h"

Brick::Brick(const std::string& fileName, float x, float y, bool t)
{
	if (!texture.loadFromFile(fileName))
	{
		std::cout << "ERROR::BRICK::BRICK" << std::endl;
	}
	teleport = t;
	sprite.setTexture(texture);
	sprite.setPosition((float)x * texture.getSize().x, (float)y * texture.getSize().y);
}

Brick::~Brick()
{

}

const bool Brick::getTeleport()
{
	return teleport;
}

const sf::FloatRect Brick::getGlobalBounds() const
{
	return sprite.getGlobalBounds();
}

void Brick::render(sf::RenderTarget* target)
{
	target->draw(sprite);
}
