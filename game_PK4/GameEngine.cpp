#include "GameEngine.h"

GameEngine::GameEngine()
{
	window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "GAME", sf::Style::Fullscreen);
	//window = new sf::RenderWindow(sf::VideoMode(1000,800), "GAME");
	window->setFramerateLimit(60);
	window->setVerticalSyncEnabled(false);

	if (!font.loadFromFile("Fonts/monarch.ttf"))
		std::cout << "ERROR::GAME::INIGUI" << std::endl;

	gameText.setFont(font);
	gameText.setCharacterSize(70);
	gameText.setFillColor(sf::Color::White);
	gameText.setString("\"Game\"");
	gameText.setPosition(window->getSize().x / 2.f - gameText.getLocalBounds().width / 2.f, 200);

	startText.setFont(font);
	startText.setCharacterSize(70);
	startText.setFillColor(sf::Color::White);
	startText.setString("Start");
	startText.setPosition(window->getSize().x / 2.f - startText.getLocalBounds().width / 2.f, 500);

	exitText.setFont(font);
	exitText.setCharacterSize(70);
	exitText.setFillColor(sf::Color::White);
	exitText.setString("Exit");
	exitText.setPosition(window->getSize().x / 2.f - exitText.getLocalBounds().width / 2.f, 800);

	pointer.setFillColor(sf::Color::Yellow);
	pointer.setRadius(10.f);

	startMenu = true;
}

GameEngine::~GameEngine()
{

}

void GameEngine::start()
{
	player = new Player();

	view = new sf::View(sf::FloatRect(0.f, 0.f, 320.f, 240.f));

	mapNumer = 0;
	imageMapNumer = { "images/map.png" , "images/map2.png" };
	newMap = false;
}

void GameEngine::loadMap()
{
	maps.push_back(new Map(imageMapNumer[mapNumer]));
	maps[mapNumer]->readMap();

	player->setPosition
	(maps[mapNumer]->getPlayerPosition().x * player->getGlobalBounds().width,
		maps[mapNumer]->getPlayerPosition().y * player->getGlobalBounds().height/2);
	newMap = false;
}

void GameEngine::run()
{
	while (window->isOpen())
	{
		while (startMenu)
		{
			isEvent();
			updateStart();
			renderStart();
		}

		isEvent();
		window->setView(*view);
		update();
		render();
	}
}

void GameEngine::isEvent()
{
	sf::Event e;
	while (window->pollEvent(e))
	{
		if (startMenu)
		{
			if ((e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape) ||
				(pointer.getGlobalBounds().intersects(exitText.getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Left)))
			{
				window->close();
			}
			if ((e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Enter) || 
				(pointer.getGlobalBounds().intersects(startText.getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Left)))
			{
				startMenu = false;
				start();
				loadMap();
				run();
			}
		}
		else
		{
			if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
				closeWindow();
		}

		

			
	}
}

void GameEngine::closeWindow()
{
	//czy chdcess znakonczyc gre
	//jesli tak
	window->close();
	//jesli nie
}

void GameEngine::update()
{
	if (newMap == true)
	{
		mapNumer++;
		loadMap();
	}
	player->update(maps[mapNumer], newMap);
	updateView();
}

void GameEngine::updateView()
{
	view->setCenter(player->getPosition());
}

void GameEngine::updateStart()
{
	pointer.setPosition(sf::Mouse::getPosition().x - pointer.getRadius() , sf::Mouse::getPosition().y - pointer.getRadius());

	if (pointer.getGlobalBounds().intersects(exitText.getGlobalBounds()))
	{
		exitText.setFillColor(sf::Color::Magenta);
	}
	else
		exitText.setFillColor(sf::Color::White);

	if (pointer.getGlobalBounds().intersects(startText.getGlobalBounds()))
	{
		startText.setFillColor(sf::Color::Magenta);
	}
	else
		startText.setFillColor(sf::Color::White);
}

void GameEngine::render()
{
	window->clear();

	maps[mapNumer]->render(window);

	player->render(window);

	window->display();
}

void GameEngine::renderStart()
{
	window->clear(sf::Color::Blue);

	window->draw(gameText);
	window->draw(startText);
	window->draw(exitText);
	window->draw(pointer);

	window->display();
}
