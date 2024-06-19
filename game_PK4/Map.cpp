#include "Map.h"

void Map::readMap(std::vector<Enemy*>& enemies, std::vector<Health*>& health, std::vector<Item*>& items)
{
    for (unsigned int x = 0; x < image.getSize().x; ++x) 
    {
        for (unsigned int y = 0; y < image.getSize().y; ++y)
        {
            sf::Color pixelColor = image.getPixel(x, y);

            if (pixelColor == sf::Color(0, 0, 0))
            {
                blocks.push_back(new Brick{ (float)x, (float)y });
            }
            else if (pixelColor == sf::Color(237, 28, 36))
            {
                playerPosition = { float(x), float(y) };
            }
            else if (pixelColor == sf::Color(0, 162, 232))
            {
                blocks.push_back(new Teleport{ (float)x, (float)y });
            }
            else if (pixelColor == sf::Color(255, 242, 0))
            {
                blocks.push_back(new Spikes{ (float)x, (float)y });
            }
            else if (pixelColor == sf::Color(255, 201, 14))
            {
                enemies.push_back(new Ghost{ (float)x, (float)y });
            }
            else if (pixelColor == sf::Color(255, 127, 39))
            {
                enemies.push_back(new Shadow{ (float)x, (float)y });
            }
            else if (pixelColor == sf::Color(63, 72, 204)) 
            {
                enemies.push_back(new Boss{ (float)x, (float)y, &enemies });
            }
            else if (pixelColor == sf::Color(34, 177, 76))
            {
                health.push_back(new Health{ (float)x, (float)y });
            }
            else if (pixelColor == sf::Color(255, 174, 201))
            {
                items.push_back(new Item{ "images/shield.png", (float)x, (float)y, 1 });
            }
            else if (pixelColor == sf::Color(200, 191, 231))
            {
                items.push_back(new Item{ "images/fire-bullet.png", (float)x, (float)y, 2 });
            }
        }
    }
}

Map::Map(const std::string& fileName)
{
	if (!image.loadFromFile(fileName))
	{
		std::cout << "ERROR::MAP::MAP";
	}
}

Map::~Map()
{
    for (int i = blocks.size() - 1; i >= 0; --i)
    {
        delete blocks[i];
        blocks.erase(blocks.begin() + i);
    }
}

std::vector<Block*> Map::getBlocks()
{
    return blocks;
}

sf::Vector2f Map::getPlayerPosition()
{
    return playerPosition;
}

void Map::render(sf::RenderTarget* target)
{
    for (auto& block : blocks)
    {
        block->render(target);
    }
}

