#include "Brick.h"

Brick::Brick(float x, float y)
{
	if (!texture.loadFromFile("images/cegla.png"))
	{
		std::cout << "ERROR::BRICK::BRICK" << std::endl;
	}

	sprite.setTexture(texture);
	sprite.setPosition((float)x * texture.getSize().x, (float)y * texture.getSize().y);
}

Brick::~Brick()
{

}

const sf::FloatRect Brick::getGlobalBounds() const
{
	return sprite.getGlobalBounds();
}

void Brick::render(sf::RenderTarget* target)
{
	target->draw(sprite);
}
