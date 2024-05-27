#include "Player.h"

Player::Player()
{
	animState = PLAYER_ANIMATION_STATES::IDLE;

	if (!texture.loadFromFile("images/player.png"))
	{
		std::cout << "ERROR::PLAYER::PLAYER" << std::endl;
	}
	sprite.setTexture(texture);

	currentFrame = sf::IntRect(0, 0, 15, 31);
	sprite.setTextureRect(sf::IntRect(currentFrame));

	isShield = true;
	attackCooldownMax = 10.f;
	attackCooldown = attackCooldownMax;

	canJump = true;
}

Player::~Player()
{

}

const sf::Vector2f Player::getPosition() const
{
	return sprite.getPosition();
}

void Player::setPosition(const float x, const float y)
{
	sprite.setPosition(x, y);
}

const sf::FloatRect Player::getGlobalBounds() const
{
	return sprite.getGlobalBounds();
}

const sf::Vector2f Player::getVelocity() const
{
	return velocity;
}

void Player::updateMovement(Map* map, bool& newMap)
{
	vel.x = 0.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		vel.x += 1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		vel.x -= 1.f;
	}
	vel.x *= 2.f;

	vel.y += 0.5f;
	if (vel.y > 8.f)
		vel.y = 8.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && canJump)
	{
		vel.y = -8.f;
		canJump = false;
	}

	if(isShield==false || !(sf::Mouse::isButtonPressed(sf::Mouse::Right)))
		sprite.move(vel.x, 0.f);

	for (auto& brick : map->getBricks())
	{
		if (getGlobalBounds().intersects(brick->getGlobalBounds()))
		{
			if (brick->getTeleport() == true)
			{
				newMap = true;
			}
			else
			{
				sprite.move(-vel.x, 0.f);
				break;
			}
		}
	}

	sprite.move(0.f, vel.y);

	for (auto& brick : map->getBricks())
	{
		if (getGlobalBounds().intersects(brick->getGlobalBounds()))
		{
			if (brick->getTeleport() == true)
			{
				newMap = true;
			}
			else
			{
				if (vel.y > 0.f)
					canJump = true;

				sprite.move(0.f, -vel.y);
				vel.y = 0.f;
				break;
			}
		}
		else
		{
			canJump = false;
		}
	}
	updateAnimState(vel);
}

void Player::updateAnimState(const sf::Vector2f& vel)
{
	if (isShield == true && sf::Mouse::isButtonPressed(sf::Mouse::Right) && attackTimer.getElapsedTime().asSeconds() > 0.25f)
	{
		animState = PLAYER_ANIMATION_STATES::USE_SHIELD;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && weapon == 1 && canAttack())
	{
		if (vel.x == 0)
			animState = PLAYER_ANIMATION_STATES::FIGHTING_1;
		else
			animState = PLAYER_ANIMATION_STATES::FIGHTING_1_RUN;
		attackTimer.restart();
	}
	else if (vel.x > 0.f && attackTimer.getElapsedTime().asSeconds() > 0.25f)
	{
		animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
	}
	else if (vel.x < 0.f && attackTimer.getElapsedTime().asSeconds() >0.25f)
	{
		animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
	}
	else if (attackTimer.getElapsedTime().asSeconds() > 0.25f)
	{
		animState = PLAYER_ANIMATION_STATES::IDLE;
	}
}

void Player::move(const float dir_x, const float dir_y)
{
	velocity.x = dir_x;
	velocity.y = dir_y;

	sprite.move(velocity);
}

const bool Player::canAttack()
{
	if (attackCooldown >= attackCooldownMax)
	{
		attackCooldown = attackCooldown - 1.f;
		return true;
	}
	return false;
}


void Player::upedateAttack()
{
	if (attackCooldown <= attackCooldownMax)
	{
		attackCooldown += 0.02f;
	}
}

void Player::updateAnimations()
{
	if (animState == PLAYER_ANIMATION_STATES::IDLE)
	{
		currentFrame.top = 0.f;
		if (animationTimer.getElapsedTime().asSeconds() >= 0.2f)
		{
			currentFrame.left += 16.f;
			if (currentFrame.left >= 63.f || currentFrame.left <= 0.f)
				currentFrame.left = 0.f;

			animationTimer.restart();
			sprite.setTextureRect(currentFrame);
		}
	}
	else if (animState == PLAYER_ANIMATION_STATES::MOVING_RIGHT)
	{
		currentFrame.top = 32.f;
		if (animationTimer.getElapsedTime().asSeconds() >= 0.1f )
		{
			currentFrame.left += 16.f;
			if (currentFrame.left >= 63.f || currentFrame.left <= 0.f)
				currentFrame.left = 0.f;

			animationTimer.restart();
			sprite.setTextureRect(currentFrame);
		}
		sprite.setScale(1.f, 1.f);
		sprite.setOrigin(0.f, 0.f);
	}
	else if (animState == PLAYER_ANIMATION_STATES::MOVING_LEFT)
	{
		currentFrame.top = 32.f;
		if (animationTimer.getElapsedTime().asSeconds() >= 0.1f )
		{
			currentFrame.left += 16.f;
			if (currentFrame.left >= 63.f || currentFrame.left <= 0.f)
				currentFrame.left = 0.f;

			animationTimer.restart();
			sprite.setTextureRect(currentFrame);
		}
		sprite.setScale(-1.f, 1.f);
		sprite.setOrigin(sprite.getGlobalBounds().width, 0.f);
	}
	else if (animState == PLAYER_ANIMATION_STATES::FIGHTING_1)
	{
		currentFrame.top = 128.f;
		if (animationTimer.getElapsedTime().asSeconds() >= 0.05f)
		{
			currentFrame.left += 16.f;
			if (currentFrame.left >= 63.f || currentFrame.left <= 0.f)
				currentFrame.left = 0.f;

			animationTimer.restart();
			sprite.setTextureRect(currentFrame);
		}
	}
	else if (animState == PLAYER_ANIMATION_STATES::FIGHTING_1_RUN)
	{
		currentFrame.top = 96.f;
		if (animationTimer.getElapsedTime().asSeconds() >= 0.05f)
		{
			currentFrame.left += 16.f;
			if (currentFrame.left >= 63.f || currentFrame.left <= 0.f)
				currentFrame.left = 0.f;

			animationTimer.restart();
			sprite.setTextureRect(currentFrame);
		}
	}
	else if (animState == PLAYER_ANIMATION_STATES::USE_SHIELD)
	{
		currentFrame.top = 160.f;	
		sprite.setTextureRect(currentFrame);
	}
	else
		animationTimer.restart();
}

void Player::update(Map* map, bool& newMap)
{
	upedateAttack();
	updateMovement(map, newMap);
	updateAnimations();
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(sprite);
}