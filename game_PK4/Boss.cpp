#include "Boss.h"


Boss::Boss(const float& x, const float& y, std::vector<Enemy*>* enemies) : enemies_(enemies)
{
	if (!texture.loadFromFile("images/Boss.png"))
	{
		std::cout << "ERROR::BOSS::BOSS" << std::endl;
	}
	sprite.setTexture(texture);

	if (!soundsBlaster.openFromFile("sounds/blaster.ogg"))
	{
		std::cout << "ERROR::GAMEENGINE::GAMEENGINE::SOUNDSITEM" << std::endl;
	}

	sprite.setPosition((float)x * texture.getSize().x /2, (float)y * texture.getSize().y / 3);
	startPosition = (sf::Vector2i)sprite.getPosition();
	goToPosition = (sf::Vector2i)sprite.getPosition();

	velocity.x = 0.f;
	velocity.y = 0.1f;

	attakPair = { {0,true}, {1,true}, {2,false} };
	attackNumber = 0;

	isGoToPosition = false;
	isStartPosition = true;

	MaxHp = 30;
	Hp = MaxHp;

	Cp = 4;
}

Boss::~Boss()
{

}

void Boss::updateMove(const sf::Vector2f& playerPosition)
{
	if (sprite.getPosition().y < startPosition.y - 16.f )
	{
		velocity.y *= -1;
	}
	else if (sprite.getPosition().y > startPosition.y + 16.f )
	{
		velocity.y *= -1;
	}

	sprite.move(velocity);
}

void Boss::goTo(sf::Vector2i position)
{
	if (fabs(position.x - sprite.getPosition().x) < 3.f)
	{
		velocity.x = position.x - sprite.getPosition().x;
	}
	else if (sprite.getPosition().x == position.x)
	{
		velocity.x = 0.f;
	}
	else if (position.x - sprite.getPosition().x < 0.f)
	{
		velocity.x = -3.f;
	}
	else if (position.x - sprite.getPosition().x > 0.f)
	{
		velocity.x = 3.f;
	}

	if (fabs(position.y - sprite.getPosition().y) < 3.f)
	{
		velocity.y = position.y - sprite.getPosition().y;
	}
	else if (sprite.getPosition().y == position.y)
	{
		velocity.y = 0.f;
	}
	else if (position.y - sprite.getPosition().y < 0)
	{
		velocity.y = -3.f;
	}
	else if (position.y - sprite.getPosition().y > 0)
	{
		velocity.y = 3.f;
	}
	sprite.move(velocity);
}

void Boss::goToStartPosition()
{
	if ((sf::Vector2i)sprite.getPosition() != startPosition)
	{		
		velocity.y = 3.f;
		velocity.x = 3.f;
	}

	goTo(startPosition);

	if ((sf::Vector2i)sprite.getPosition() == startPosition)
	{
		isStartPosition = true;
		isGoToPosition = false;
		canAttack.restart();

		attackNumber = -1;

		velocity.y = 0.2f;
		velocity.x = 0.f;
	}
}

void Boss::updateAttack(const sf::Vector2f& playerPosition, std::vector<BossBullet*>& bossBullets)
{
	
	if (canAttack.getElapsedTime().asSeconds() > 3.f)
	{
		while (attackNumber == -1)
		{
			int randomAttackNumber = rand() % 3;

			auto filteredView = attakPair | std::views::filter([randomAttackNumber](const std::pair<int, bool>& p)
				{return p.first == randomAttackNumber && p.second;	});

			for (const auto& p : filteredView)
			{
				attackNumber = p.first;
				break;
			}
		}
		goToPosition.x = playerPosition.x;
		goToPosition.y = playerPosition.y -16.f;

		isStartPosition = false;
		
		canAttack.restart();
		//
		//attackNumber = 2;
	}

	switch (attackNumber)
	{
	case 0:
		attack_1();
		break;
	case 1:
		attack_2(bossBullets);
		break;
	case 2:
		attack_3();
	default:
		attack_1();
	}
}

void Boss::attack_1()
{
	if ((sf::Vector2i)sprite.getPosition() != goToPosition)
	{
		velocity.y = 3.f;
		velocity.x = 3.f;

		goTo(goToPosition);
	}

	if ((sf::Vector2i)sprite.getPosition() == (sf::Vector2i)goToPosition)
	{
		isGoToPosition = true;
	}
}

void Boss::attack_2(std::vector<BossBullet*>& bossBullets)
{
	soundsBlaster.play();

	bossBullets.push_back(new BossBullet(sprite.getGlobalBounds().left,
		sprite.getGlobalBounds().top + sprite.getGlobalBounds().width / 2.f, 1));

	bossBullets.push_back(new BossBullet(sprite.getGlobalBounds().left,
		sprite.getGlobalBounds().top + sprite.getGlobalBounds().width / 2.f, -1));

	isGoToPosition = true;
	isStartPosition = false;
}

void Boss::attack_3()
{
	if(enemies_->size() < 2)
		enemies_->push_back(new Ghost(170.f / 16.f, 140.f /32.f *2.f));
	isGoToPosition = true;
}

void Boss::update(const sf::Vector2f& playerPosition, std::vector<BossBullet*>& bossBullets)
{
	if (Hp <= 15)
		attakPair[2].second = true;

	if (canAttack.getElapsedTime().asSeconds() > 3)
	{
		isStartPosition = false;	
	}

	if (isStartPosition == false)
	{
		if (isGoToPosition == true && isStartPosition == false)
		{
			goToStartPosition();
		}
		else
		{
			updateAttack(playerPosition, bossBullets);
		}
	}
	else
	{
		updateMove(playerPosition);
	}

	if (gotDamageTimer.getElapsedTime().asSeconds() > 0.25f)
		sprite.setColor(sf::Color(255, 255, 255));
}
