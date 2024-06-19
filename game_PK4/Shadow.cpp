#include "Shadow.h"

Shadow::Shadow(const float& x, const float& y)
{
	if (!texture.loadFromFile("images/Shadow.png"))
	{
		std::cout << "ERROR::SHADOW::SHADOW" << std::endl;
	}
	sprite.setTexture(texture);
	
	sprite.setPosition((float)x * texture.getSize().x, (float)y * texture.getSize().y / 2);
	sprite.setScale(-1.f, 1.f);
	startPosition = sprite.getPosition();
	sprite.setOrigin(sprite.getGlobalBounds().width, 0.f);

	velocity.x = 0.5;
	velocity.y = 0;

	MaxHp = 7;
	Hp = MaxHp;

	Cp = 5;
}

Shadow::~Shadow()
{

}

void Shadow::updateMove(const sf::Vector2f& playerPosition)
{
	if (fabs(playerPosition.x - sprite.getGlobalBounds().left) <= 160 && (fabs(playerPosition.y - sprite.getGlobalBounds().top) <= 160))
	{
		if (sprite.getPosition().x < startPosition.x - 64.f && moveTimer.getElapsedTime().asSeconds() > 0.25f)
		{
			velocity.x *= -1;
			sprite.setScale(-1.f, 1.f);
			sprite.setOrigin(sprite.getGlobalBounds().width, 0.f);
		}
		else if (sprite.getPosition().x > startPosition.x + 64.f && moveTimer.getElapsedTime().asSeconds() > 0.25f)
		{
			velocity.x *= -1;
			sprite.setScale(1.f, 1.f);
			sprite.setOrigin(0.f, 0.f);
		}

		sprite.move(velocity);
	}
}

void Shadow::update(const sf::Vector2f& playerPosition, std::vector<BossBullet*>& bossBullets)
{
	updateMove(playerPosition);

	if (gotDamageTimer.getElapsedTime().asSeconds() > 0.25f)
		sprite.setColor(sf::Color(255, 255, 255));
}