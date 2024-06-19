#include "Ghost.h"

Ghost::Ghost(const float& x, const float& y)
{
	if (!texture.loadFromFile("images/ghost.png"))
	{
		std::cout << "ERROR::GHOST::GHOST" << std::endl;
	}
	sprite.setTexture(texture);
	sprite.setColor(sf::Color(255, 255, 255, 100));
	sprite.setPosition((float)x * texture.getSize().x + 3.F * x, (float)y * texture.getSize().y /2);
	
	MaxHp = 5;
	Hp = MaxHp;

	Cp = 2;
}

Ghost::~Ghost()
{

}

void Ghost::updateMove(const sf::Vector2f& playerPosition)
{
	velocity.x = 0;
	velocity.y = 0;

	if (fabs(playerPosition.x - sprite.getGlobalBounds().left) <= 160 && (fabs(playerPosition.y - sprite.getGlobalBounds().top) <= 160))
	{
		if (playerPosition.x - sprite.getGlobalBounds().left < 0.f && moveTimer.getElapsedTime().asSeconds() > 0.25f)
		{
			velocity.x = -0.7f;
			sprite.setScale(1.f, 1.f);
			sprite.setOrigin(0.f, 0.f);
		}
		else if (playerPosition.x - sprite.getGlobalBounds().left > 0.f && moveTimer.getElapsedTime().asSeconds() > 0.25f)
		{
			velocity.x = 0.7f;
			sprite.setScale(-1.f, 1.f);
			sprite.setOrigin(sprite.getGlobalBounds().width, 0.f);
		}

		if (playerPosition.y - sprite.getGlobalBounds().top < 0 && moveTimer.getElapsedTime().asSeconds() > 0.25f)
		{
			velocity.y = -0.7f;
		}
		else if (playerPosition.y - sprite.getGlobalBounds().top > 0 && moveTimer.getElapsedTime().asSeconds() > 0.25f)
		{
			velocity.y = 0.7f;
		}

		sprite.move(velocity);
	}
}

void Ghost::update(const sf::Vector2f& playerPosition, std::vector<BossBullet*>& bossBullets, std::vector<Enemy*>& enemies)
{
	updateMove(playerPosition);
	if(gotDamageTimer.getElapsedTime().asSeconds() > 0.25f)
		sprite.setColor(sf::Color(255, 255, 255, 100));
}
