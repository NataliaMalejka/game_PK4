#include "Item.h"

Item::Item(const std::string& fileName, const float& x, const float& y, const int& i)
{
	if (!texture.loadFromFile(fileName))
	{
		std::cout << "ERROR::ITEM::ITEM" << std::endl;
	}

	sprite.setTexture(texture);
	sprite.setPosition((float)x * texture.getSize().x, (float)y * texture.getSize().y);

	vectorNr = i;
}

Item::~Item()
{

}

void Item::getItem(std::vector<bool>& vec)
{
	vec[vectorNr] = true;
}

const sf::FloatRect& Item::getGlobalBounds()
{
	return sprite.getGlobalBounds();
}

void Item::render(sf::RenderTarget* target)
{
	target->draw(sprite);
}
