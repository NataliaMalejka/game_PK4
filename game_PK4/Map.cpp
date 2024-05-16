#include "Map.h"

void Map::readMap()
{
    for (unsigned int x = 0; x < image.getSize().x; ++x) 
    {
        for (unsigned int y = 0; y < image.getSize().y; ++y)
        {
            sf::Color pixelColor = image.getPixel(x, y);

            if (pixelColor == sf::Color(0, 0, 0))
            {
                bricks.push_back(new Brick{ "images/cegla.png", (float)x, (float)y, false });
            }
            else if (pixelColor == sf::Color(237, 28, 36))
            {
                playerPosition = { float(x), float(y) };
            }
            else if (pixelColor == sf::Color(0, 162, 232))
            {
                bricks.push_back(new Brick{ "images/teleport.png", (float)x, (float)y, true });
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
    for (int i = 0; i < bricks.size(); i++)
    {
        delete bricks[i];
        bricks[i] = nullptr;
    }
}

std::vector<Brick*> Map::getBricks()
{
    return bricks;
}

sf::Vector2f Map::getPlayerPosition()
{
    return playerPosition;
}

void Map::render(sf::RenderTarget* target)
{
    for (auto brick : bricks)
    {
        brick->render(target);
    }
}

