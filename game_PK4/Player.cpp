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

	vel.y += 0.2f;
	if (vel.y > 3.f)
		vel.y = 3.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && canJump)
	{
		vel.y = -6.f;
		canJump = false;
	}

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

	if (this->vel.x > 0.f)
		this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
	else if (this->vel.x < 0.f)
		this->animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
	else
		this->animState = PLAYER_ANIMATION_STATES::IDLE;
}

void Player::move(const float dir_x, const float dir_y)
{
	velocity.x = dir_x;
	velocity.y = dir_y;

	sprite.move(velocity);
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
		this->sprite.setScale(1.f, 1.f);
		this->sprite.setOrigin(0.f, 0.f);
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_LEFT)
	{
		this->currentFrame.top = 32.f;
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f )
		{
			this->currentFrame.left += 16.f;
			if (currentFrame.left >= 63.f || currentFrame.left <= 0.f)
				this->currentFrame.left = 0.f;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(-1.f, 1.f);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width, 0.f);
	}
	else
		this->animationTimer.restart();
}

void Player::update(Map* map, bool& newMap)
{
	updateMovement(map, newMap);
	updateAnimations();
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(sprite);
}