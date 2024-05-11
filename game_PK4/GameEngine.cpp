#include "GameEngine.h"

GameEngine::GameEngine()
{
	window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "GAME", sf::Style::Fullscreen);
	window->setFramerateLimit(60);
	window->setVerticalSyncEnabled(false);

	player = new Player();

	mapNumer = 0;
	imageMapNumer = {"images/map.png"};
}

GameEngine::~GameEngine()
{

}

void GameEngine::start()
{
	//strat window
	
	//czy chcesz zaczac gre?
	//jesli tak
	loadMap();
	run();
	//jesli nie


}

void GameEngine::loadMap()
{
	maps.push_back(new Map(imageMapNumer[mapNumer]));
	maps[mapNumer]->readMap();

	player->setPosition
	(maps[mapNumer]->getPlayerPosition().x * player->getGlobalBounds().width,
		maps[mapNumer]->getPlayerPosition().y * player->getGlobalBounds().height);
}

void GameEngine::run()
{
	while (window->isOpen())
	{
		isEvent();
		update();
		render();
	}
}

void GameEngine::isEvent()
{
	sf::Event e;
	while (window->pollEvent(e))
	{
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			close();
	}
}

void GameEngine::close()
{
	//czy chdcess znakonczyc gre
	//jesli tak
	window->close();
	//jesli nie
}


void GameEngine::updateCollision()
{
	for (auto& brick : maps[mapNumer]->getBricks())
	{
		//usuwa pociski


		if (player->getGlobalBounds().intersects(brick->getGlobalBounds()))
		{
			//bottom
			if (player->getGlobalBounds().top < brick->getGlobalBounds().top
				&& player->getGlobalBounds().top + player->getGlobalBounds().height < brick->getGlobalBounds().top + brick->getGlobalBounds().height
				&& player->getGlobalBounds().left < brick->getGlobalBounds().left + brick->getGlobalBounds().width
				&& player->getGlobalBounds().left + player->getGlobalBounds().width > brick->getGlobalBounds().left)
			{
				player->setPosition(player->getGlobalBounds().left, brick->getGlobalBounds().top - player->getGlobalBounds().height);
				player->canJump = true;
			}
			//top
			else if (player->getGlobalBounds().top > brick->getGlobalBounds().top
				&& player->getGlobalBounds().top + player->getGlobalBounds().height > brick->getGlobalBounds().top + brick->getGlobalBounds().height
				&& player->getGlobalBounds().left < brick->getGlobalBounds().left + brick->getGlobalBounds().width
				&& player->getGlobalBounds().left + player->getGlobalBounds().width > brick->getGlobalBounds().left)
			{
				player->setPosition(player->getGlobalBounds().left, brick->getGlobalBounds().top + brick->getGlobalBounds().height);
				
			}
			
			//left
			if (player->getGlobalBounds().left > brick->getGlobalBounds().left
				&& player->getGlobalBounds().left + player->getGlobalBounds().width > brick->getGlobalBounds().left + brick->getGlobalBounds().width
				&& player->getGlobalBounds().top < brick->getGlobalBounds().top + brick->getGlobalBounds().height
				&& player->getGlobalBounds().top + player->getGlobalBounds().height > brick->getGlobalBounds().top)
			{
				player->setPosition(brick->getGlobalBounds().left + player->getGlobalBounds().width, player->getGlobalBounds().top);
			}
			//right
			else if (player->getGlobalBounds().left < brick->getGlobalBounds().left
				&& player->getGlobalBounds().left + player->getGlobalBounds().width < brick->getGlobalBounds().left + brick->getGlobalBounds().width
				&& player->getGlobalBounds().top < brick->getGlobalBounds().top + brick->getGlobalBounds().height
				&& player->getGlobalBounds().top + player->getGlobalBounds().height > brick->getGlobalBounds().top)
			{
				player->setPosition(brick->getGlobalBounds().left - player->getGlobalBounds().width, player->getGlobalBounds().top);
			}

		}
	}
}

void GameEngine::update()
{
	player->update();

	updateCollision();

}

void GameEngine::render()
{
	window->clear();

	maps[mapNumer]->render(window);

	player->render(window);

	window->display();
}
