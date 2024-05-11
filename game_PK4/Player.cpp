#include "Player.h"

Player::Player()
{
	if (!texture.loadFromFile("images/kot1SFML.png"))
	{
		std::cout << "ERROR::PLAYER::PLAYER" << std::endl;
	}
	sprite.setTexture(texture);

	velocity = { 0.f,0.f };
	velocityMax = { 4.f,10.f };
	velocityMin = 1.f;
	gravity = 5.f;
	acceleration = 0.5f;
	drag = 0.5f;

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

void Player::updateMovement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		move(3.f, 0.f);
		//this->animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		move(-3.f, 0.f);
		//this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && canJump)
	{
		jump();
		//this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
	}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	//{
	//	move(0.f, 1.f);
	//	//this->animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
	//}
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	//{
	//	move(0.f, -1.f);
	//	//this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
	//}
}

void Player::move(const float dir_x, const float dir_y)
{
	velocity.x = dir_x;

	if (std::abs(velocity.x) > velocityMax.x)
	{
		velocity.x = velocityMax.x * ((velocity.x < 0.f) ? -1.f : 1.f);
	}

	sprite.move(velocity.x, 0.f);
}

void Player::updatePhysics()
{
	this->velocity.y += 1.f * this->gravity;
	
	this->velocity *= this->drag;
	
	if (std::abs(this->velocity.x) < this->velocityMin)
		this->velocity.x = 0.f;
	if (std::abs(this->velocity.y) < this->velocityMin)
		this->velocity.y = 0.f;

	this->sprite.move(this->velocity);
}

void Player::jump()
{
	velocity.y = -60.f;
	canJump = false;
}

void Player::update()
{
	updateMovement();
	updatePhysics();
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(sprite);
}
