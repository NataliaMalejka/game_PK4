#include "Health.h"

Health::Health(const float& x, const float& y)
{
	if (!texture.loadFromFile("images/health.png"))
	{
		std::cout << "ERROR::HEALTH::HEALTH" << std::endl;
	}

	sprite.setTexture(texture);
	sprite.setPosition((float)x * texture.getSize().x, (float)y * texture.getSize().y);

	addHp = 5;
}

Health::~Health()
{

}

const sf::FloatRect& Health::getGlobalBounds() const
{
	return sprite.getGlobalBounds();
}

const int& Health::getAddHp() const
{
	return addHp;
}

void Health::render(sf::RenderTarget* target)
{
	target->draw(sprite);
}
