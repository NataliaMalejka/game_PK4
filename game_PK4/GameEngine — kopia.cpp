#include "GameEngine.h"

GameEngine::GameEngine()
{
	window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "GAME", sf::Style::Fullscreen);
	//window = new sf::RenderWindow(sf::VideoMode(1000,800), "GAME");
	window->setFramerateLimit(60);
	window->setVerticalSyncEnabled(false);

	std::filesystem::path fontPath = "Fonts/monarch.ttf";

	if (!std::filesystem::exists(fontPath)) 
		std::cout << "ERROR::GAME::INIGUI::FONT FILE DOES NOT EXIST" << std::endl;

	if (!font.loadFromFile(fontPath.string())) 
		std::cout << "ERROR::GAME::INIGUI::FAILED TO LOAD FONT" << std::endl;

	gameText.setFont(font);
	gameText.setCharacterSize(70);
	gameText.setFillColor(sf::Color::White);
	gameText.setString("\"Game\"");
	gameText.setPosition(window->getSize().x / 2.f - gameText.getLocalBounds().width / 2.f, 200);

	playText = gameText;
	playText.setString("Start");
	playText.setPosition(window->getSize().x / 2.f - playText.getLocalBounds().width / 2.f, 500);

	exitText = gameText;
	exitText.setString("Exit");
	exitText.setPosition(window->getSize().x / 2.f - exitText.getLocalBounds().width / 2.f, 800);

	pointer.setFillColor(sf::Color::Yellow);
	pointer.setRadius(10.f);

	startMenu = true;
	pauseMenu = false;
}

GameEngine::~GameEngine()
{
	delete window;
	delete player;
	delete view;

	for (int i = maps.size() - 1; i >= 0; --i)
	{
		delete maps[i];
		maps.erase(maps.begin() + i);
	}

	for (int i = enemies.size() - 1; i >= 0; --i)
	{
		delete enemies[i];
		enemies.erase(enemies.begin() + i);
	}

	for (int i = bullets.size() - 1; i >= 0; --i)
	{
		delete bullets[i];
		bullets.erase(bullets.begin() + i);
	}

	for (int i = bossBullets.size() - 1; i >= 0; --i)
	{
		delete bossBullets[i];
		bossBullets.erase(bossBullets.begin() + i);
	}

	for (int i = health.size() - 1; i >= 0; --i)
	{
		delete health[i];
		health.erase(health.begin() + i);
	}

	for (int i = items.size() - 1; i >= 0; --i)
	{
		delete items[i];
		items.erase(items.begin() + i);
	}
}

void GameEngine::start()
{
	player = new Player();

	view = new sf::View(sf::FloatRect(0.f, 0.f, 320.f, 240.f));

	mapNumer = 0;
	imageMapNumer = { "images/map.png" , "images/map2.png", "images/map3.png" };
	newMap = false;

	pointer.setScale(0.2f, 0.2f);

	gameText.setScale(0.2f, 0.2f);
	exitText.setScale(0.2f, 0.2f);

	playText.setString("Continue");
	playText.setScale(0.2f, 0.2f);

	gameOverText = playText;
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setString("Game Over");

	playerHpBar.setSize(sf::Vector2f(50.f, 10.f));
	playerHpBar.setFillColor(sf::Color::Green);

	playerHpBarBack = playerHpBar;
	playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));

	playerBulletBar.setSize(sf::Vector2f(50.f, 3.f));
	playerBulletBar.setFillColor(sf::Color::Magenta);

	playerBulletBarBack = playerBulletBar;
	playerBulletBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}

void GameEngine::loadMap()
{
	for (int i = enemies.size() - 1; i >= 0; --i)
	{
		delete enemies[i];
		enemies.erase(enemies.begin() + i);
	}

	for (int i = bullets.size() - 1; i >= 0; --i)
	{
		delete bullets[i];
		bullets.erase(bullets.begin() + i);
	}

	for (int i = bossBullets.size() - 1; i >= 0; --i)
	{
		delete bossBullets[i];
		bossBullets.erase(bossBullets.begin() + i);
	}

	for (int i = health.size() - 1; i >= 0; --i)
	{
		delete health[i];           
		health.erase(health.begin() + i);  
	}

	for (int i = items.size() - 1; i >= 0; --i)
	{
		delete items[i];
		items.erase(items.begin() + i);
	}

	maps.push_back(new Map(imageMapNumer[mapNumer]));
	maps[mapNumer]->readMap(enemies, health, items);

	player->setPosition
	(maps[mapNumer]->getPlayerPosition().x * player->getGlobalBounds().width,
		maps[mapNumer]->getPlayerPosition().y * player->getGlobalBounds().height / 2);
	newMap = false;
}

void GameEngine::run()
{
	while (window->isOpen())
	{
		if ((startMenu || pauseMenu) && window->isOpen())
		{
			isEvent();
			updateButton(playText);
			updateButton(exitText);
			renderMenu();
		}
		else
		{
			isEvent();
			window->setView(*view);

			if (player->getHp() > 0)
				update();

			render();
		}
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
				startMenu = false;
				window->close();
			}
			else if ((e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Enter) ||
				(pointer.getGlobalBounds().intersects(playText.getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Left)))
			{
				startMenu = false;
				start();
				loadMap();
			}
		}
		else if (pauseMenu)
		{
			if ((pointer.getGlobalBounds().intersects(exitText.getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Left)))
			{
				pauseMenu = false;
				window->close();
			}
			else if (pointer.getGlobalBounds().intersects(playText.getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				pauseMenu = false;
			}
		}
		else
		{
			if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			{
				if (player->getHp() > 0.f)
				{
					pauseMenu = true;
					gameText.setPosition((view->getCenter().x - gameText.getGlobalBounds().width / 2.f), view->getCenter().y - 70.f);
					playText.setPosition((view->getCenter().x - playText.getGlobalBounds().width / 2.f), view->getCenter().y - 10.f);
					exitText.setPosition((view->getCenter().x - exitText.getGlobalBounds().width / 2.f), view->getCenter().y + 60.f);
				}
				else
					window->close();
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && player->getUseShield() == false && player->getIsBullet()
				&& player->getWeapon() == 2 && player->canAttackBullet())
			{
				bullets.push_back(new Bullet(player->getGlobalBounds().left, 
					player->getGlobalBounds().top + player->getGlobalBounds().width /2.f, player->getDirection()));
			}
			else if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Num1 && player->getUseShield()==false)
			{
				player->setWeapon(0);
			}
			else if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Num2 && player->getUseShield() == false && player->getIsBullet())
			{
				player->setWeapon(2);
			}
		}
	}
}

void GameEngine::update()
{
	if (newMap == true)
	{
		mapNumer++;
		loadMap();
	}
	player->update(maps[mapNumer], newMap);

	std::vector<std::thread> threads;

	for (auto& bullet : bullets)
	{
		threads.emplace_back(&Bullet::update, bullet);
	}

	for (auto& t : threads)
	{
		t.join();
	}

	for (auto& bossBullet :bossBullets)
	{
		bossBullet->update();
	}

	for (auto& enemy : enemies) {
		if (enemy != nullptr) {
			try {
				enemy->update(player->getPosition(), bossBullets, enemies);
			}
			catch (const std::exception& e) {
				std::cerr << "Exception: " << e.what() << std::endl;
			}
			catch (...) {
				std::cerr << "Unknown exception occurred." << std::endl;
			}
		}
		else {
			std::cerr << "Null enemy pointer encountered!" << std::endl;
		}
	}

	updateContact();
	updateBars();
	updateView();
}

void GameEngine::updateContact()
{
	for (int i = items.size() - 1; i >= 0; --i)
	{
		if (player->getGlobalBounds().intersects(items[i]->getGlobalBounds()) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
		{
			items[i]->getItem(player->getIsWeapon());

			delete items[i];
			items.erase(items.begin() + i);
		}
	}

	for (int i = health.size() - 1; i >= 0; --i)
	{
		if (player->getGlobalBounds().intersects(health[i]->getGlobalBounds()) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
		{
			player->setHp(health[i]->getAddHp());

			delete health[i];
			health.erase(health.begin() + i);
		}
	}

	for (int i = bullets.size() - 1; i >= 0; --i)
	{
		bool deletedBullet = false;

		for (int j = enemies.size() -1; j >=0 && deletedBullet == false; --j)
		{
			if (bullets[i]->getGlobalBounds().left < enemies[j]->getGlobalBounds().left + enemies[j]->getGlobalBounds().width &&
				bullets[i]->getGlobalBounds().left + bullets[i]->getGlobalBounds().width > enemies[j]->getGlobalBounds().left &&
				bullets[i]->getGlobalBounds().top < enemies[j]->getGlobalBounds().top + enemies[j]->getGlobalBounds().height &&
				bullets[i]->getGlobalBounds().top + bullets[i]->getGlobalBounds().height > enemies[j]->getGlobalBounds().top)
			{
				enemies[j]->gotDamage(player->getWeaponDamage()[2]);
				enemies[j]->stepBack();
				enemies[j]->setGotDamageTimer();
				delete bullets[i];
				bullets.erase(bullets.begin() + i);
				deletedBullet = true;
			}
		}

		for (int k = maps[mapNumer]->getBlocks().size() - 1; k >= 0 && deletedBullet == false; --k)
		{
			if (bullets[i]->getGlobalBounds().intersects(maps[mapNumer]->getBlocks()[k]->getGlobalBounds()))
			{
				delete bullets[i];
				bullets.erase(bullets.begin() + i);
				deletedBullet = true;
			}
		}
	}

	for (int i = bossBullets.size() - 1; i >= 0; --i)
	{
		bool deletedBossBullet = false;

		if (bossBullets[i]->getGlobalBounds().intersects(player->getShieldRect()) && player->getUseShield())
		{
			delete bossBullets[i];
			bossBullets.erase(bossBullets.begin() + i);
			deletedBossBullet = true;
		}
		else if (bossBullets[i]->getGlobalBounds().intersects(player->getGlobalBounds()))
		{
			player->gotDamage(bossBullets[i]->getDamage());
			delete bossBullets[i];
			bossBullets.erase(bossBullets.begin() + i);
			deletedBossBullet = true;
		}

		for (int k = maps[mapNumer]->getBlocks().size() - 1; k >= 0 && deletedBossBullet == false; --k)
		{
			if (bossBullets[i]->getGlobalBounds().intersects(maps[mapNumer]->getBlocks()[k]->getGlobalBounds()))
			{
				delete bossBullets[i];
				bossBullets.erase(bossBullets.begin() + i);
				deletedBossBullet = true;
			}
		}
	}

	for (auto& enemy : enemies)
	{
		if (enemy->getGlobalBounds().intersects(player->getAttackRect()) && player->getAttackTimer() && enemy->getGotDamageTimer() && player->getWeapon() == 0)
		{					
			enemy->gotDamage(player->getWeaponDamage()[0]);
			enemy->stepBack();
			enemy->setGotDamageTimer();
		}

		if (enemy->getGlobalBounds().intersects(player->getShieldRect()) && player->getUseShield())
		{
			if(!dynamic_cast<Boss*>(enemy))
				enemy->stepBack();
		}
		else if (enemy->getGlobalBounds().intersects(player->getGlobalBounds()) && enemy->getAttackTimer())
		{
			std::future<const int&> future_cp = std::async(&Enemy::getCp, enemy);
			enemy->setAttackTimer();
			const int& cp = future_cp.get();
			player->gotDamage(cp);
			
		}
	}
}

void GameEngine::updateBars()
{
	float hpPercent = static_cast<float> (player->getHp()) / (player->getMaxHp());
	playerHpBar.setSize(sf::Vector2f(50.f * hpPercent, playerHpBar.getSize().y));

	playerHpBar.setPosition(player->getPosition().x - 150, player->getPosition().y - 110);
	playerHpBarBack.setPosition(player->getPosition().x - 150, player->getPosition().y - 110);

	if (player->getIsBullet())
	{
		float bulletPercent = static_cast<float> (player->getAttackCooldownBullet() / 1.f);
		playerBulletBar.setSize(sf::Vector2f(50.f * bulletPercent, playerBulletBar.getSize().y));

		playerBulletBar.setPosition(player->getPosition().x - 150, player->getPosition().y - 95);
		playerBulletBarBack.setPosition(player->getPosition().x - 150, player->getPosition().y - 95);
	}
}

void GameEngine::updateView()
{
	view->setCenter(player->getPosition());
}

void GameEngine::updateButton(sf::Text& text)
{
	if (pauseMenu)
	{
		sf::Vector2f worldPosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window), *view);
		pointer.setPosition(worldPosition.x - pointer.getRadius() * pointer.getScale().x, worldPosition.y - pointer.getRadius()*pointer.getScale().y);
	}
	else
		pointer.setPosition(sf::Mouse::getPosition().x - pointer.getRadius(), sf::Mouse::getPosition().y - pointer.getRadius());

	if (pointer.getGlobalBounds().intersects(text.getGlobalBounds()))
	{
		text.setFillColor(sf::Color::Magenta);
	}
	else
		text.setFillColor(sf::Color::White);
}

void GameEngine::renderBar()
{
	window->draw(playerHpBarBack);
	window->draw(playerHpBar);

	if (player->getIsBullet())
	{
		window->draw(playerBulletBarBack);
		window->draw(playerBulletBar);
	}
}

void GameEngine::render()
{
	window->clear();

	maps[mapNumer]->render(window);

	player->render(window);

	for (int i = enemies.size() - 1; i >= 0; --i)
	{
		if (enemies[i]->getHp() > 0)
			enemies[i]->render(window);
		else
		{
			delete enemies[i];
			enemies.erase(enemies.begin() + i);
		}
	}

	for (auto& bullet : bullets)
	{
		bullet->render(window);
	}

	for (auto& bossBullet : bossBullets)
	{
		bossBullet->render(window);
	}

	for (auto& h : health)
	{
		h->render(window);
	}

	for (auto& item : items)
	{
		item->render(window);
	}

	renderBar();

	if (player->getHp() <= 0)
	{
		gameOverText.setScale(0.25f, 0.25f);
		gameOverText.setPosition((view->getCenter().x - gameOverText.getGlobalBounds().width / 2.f), view->getCenter().y - 30.f);
		window->draw(gameOverText);
	}

	window->display();
}

void GameEngine::renderMenu()
{
	window->clear();

	window->draw(gameText);
	window->draw(playText);
	window->draw(exitText);
	window->draw(pointer);

	window->display();
}

