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

	if (!swordSounds.openFromFile("sounds/sword-sound.ogg"))
	{
		std::cout << "ERROR::PLAYER::PLAYER::MUSIC" << std::endl;
	}

	weapon = 0;
	weaponDamage = { 2,0,3 };
	isWeapon = { true, false, false };

	MaxHp = 100;
	Hp = MaxHp;

	attackCooldownMax = 1.f;
	attackCooldown = attackCooldownMax;
	attackCooldownBullet = attackCooldownMax;

	useShield = false;
	canJump = true;
}

Player::~Player()
{

}

const sf::Vector2f Player::getPosition() const
{
	return sprite.getPosition();
}

void Player::setPosition(const float& x, const float& y)
{
	sprite.setPosition(x, y);
}

const sf::FloatRect Player::getGlobalBounds() const
{
	return sprite.getGlobalBounds();
}

const sf::FloatRect Player::getGlobalBoundsY() const
{
	if (velocity.x == 0.f)
	{
		sf::FloatRect globalBounds(sprite.getGlobalBounds().left + 6, sprite.getGlobalBounds().top, 3, sprite.getGlobalBounds().height);
		return globalBounds;
	}
	else
	{
		return sprite.getGlobalBounds();
	}
}

const sf::FloatRect Player::getAttackRect() const
{
	sf::FloatRect attackRect = sprite.getGlobalBounds();
	attackRect.left += 4.f * sprite.getScale().x;
	return attackRect;
}

const sf::FloatRect Player::getShieldRect() const
{
	sf::FloatRect shieldRect = sprite.getGlobalBounds();
	shieldRect.width = 7;

	if (sprite.getScale().x == 1)
		shieldRect.left += 10;
	else
		shieldRect.left -= 1;

	return shieldRect;
}

const bool Player::getAttackTimer() const
{
	if (attackTimer.getElapsedTime().asSeconds() < 0.25f)
		return true;
	else
		return false;
}

const sf::Vector2f Player::getVelocity() const
{
	return velocity;
}

void Player::setVelocity(const float& x, const float& y)
{
	velocity.x = x;
	velocity.y = y;
}

void Player::updateMovement(Map* map, bool& newMap)
{
	velocity.x = 0.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		velocity.x += 2.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		velocity.x -= 2.f;
	}

	float direction = 0.5f * velocity.x;

	if (isWeapon[1] == false || !(sf::Mouse::isButtonPressed(sf::Mouse::Right)))
	{
		useShield = false;
		sprite.move(velocity.x, 0.f);
	}

	for (auto& block : map->getBlocks())
	{
		if (getGlobalBounds().intersects(block->getGlobalBounds()))
		{		
			if (dynamic_cast<Spikes*>(block))
			{
				gotDamage(1);
			}
			
			block->isIntersectsX(sprite, velocity, newMap, beforeJump);

			if (getGlobalBounds().intersects(block->getGlobalBounds())) 
			{
				if (getGlobalBounds().left < (block->getGlobalBounds().left + block->getGlobalBounds().width)
					&& getGlobalBounds().left  > block->getGlobalBounds().left)
					sprite.move(6.f, 0.f);

				else if ((getGlobalBounds().left + getGlobalBounds().width) > block->getGlobalBounds().left
					&& getGlobalBounds().left < block->getGlobalBounds().left)
					sprite.move(-6.f, 0.f);
			}

			break;
		}
	}
	
	velocity.y += 0.5f;
	if (velocity.y > 8.f)
		velocity.y = 8.f;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && canJump)
	{
		velocity.y = -8.f;
		canJump = false;
	}

	sprite.move(0.f, velocity.y);

	for (auto& block : map->getBlocks())
	{
		if (getGlobalBoundsY().intersects(block->getGlobalBounds()))
		{
			if (dynamic_cast<Spikes*>(block))
			{
				gotDamage(1);
				gotDamageClock.restart();
			}
			block->isIntersectsY(sprite, velocity, newMap, canJump, beforeJump);
			break;
		}
		else
		{
			canJump = false;
		}
	}
}

void Player::updateAnimState(const sf::Vector2f& vel)
{
	if(gotDamageClock.getElapsedTime().asSeconds() > 0.25f)
		sprite.setColor(sf::Color::White);

	if (isWeapon[1] == true && sf::Mouse::isButtonPressed(sf::Mouse::Right) && attackTimer.getElapsedTime().asSeconds() > 0.25f)
	{
		animState = PLAYER_ANIMATION_STATES::USE_SHIELD;
		useShield = true;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && weapon == 0 && canAttack())
	{
		swordSounds.play();

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

void Player::move(const float& dir_x, const float& dir_y)
{
	sprite.move(dir_x, dir_y);
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

const bool Player::canAttackBullet()
{
	if (attackCooldownBullet >= attackCooldownMax && isWeapon[2])
	{
		attackCooldownBullet = attackCooldownBullet - 1.f;
		return true;
	}
	return false;
}

const float& Player::getAttackCooldownBullet() const
{
	return attackCooldownBullet;
}

void Player::upedateAttack(float& attackType, const float& value)
{
	if (attackType <= attackCooldownMax)
	{
		attackType +=value;
	}
	if (attackType >= attackCooldownMax)
		attackType = attackCooldownMax;
}

void Player::gotDamage(const int& damage)
{
	Hp -= damage;
	if (Hp < 0)
		Hp = 0;

	gotDamageClock.restart();
	sprite.setColor(sf::Color(255, 0, 0));
}

const std::vector<int>& Player::getWeaponDamage() const
{
	return weaponDamage;
}

const int& Player::getWeapon()
{
	return weapon;
}

void Player::setWeapon(const int& nr)
{
	weapon = nr;
}

const bool Player::getUseShield() const
{
	return useShield;
}

const bool Player::getIsBullet() const
{
	return isWeapon[2];
}

std::vector<bool>& Player::getIsWeapon()
{
	return isWeapon;
}

void Player::updateAnimations()
{
	if (animState == PLAYER_ANIMATION_STATES::IDLE)
	{
		currentFrame.top = 0.f;
		if (animationTimer.getElapsedTime().asSeconds() >= 0.2f)
		{
			animations();
		}
	}
	else if (animState == PLAYER_ANIMATION_STATES::MOVING_RIGHT)
	{
		currentFrame.top = 32.f;
		if (animationTimer.getElapsedTime().asSeconds() >= 0.1f )
		{
			animations();
		}
		sprite.setScale(1.f, 1.f);
		sprite.setOrigin(0.f, 0.f);
	}
	else if (animState == PLAYER_ANIMATION_STATES::MOVING_LEFT)
	{
		currentFrame.top = 32.f;
		if (animationTimer.getElapsedTime().asSeconds() >= 0.1f )
		{
			animations();
		}
		sprite.setScale(-1.f, 1.f);
		sprite.setOrigin(sprite.getGlobalBounds().width, 0.f);
	}
	else if (animState == PLAYER_ANIMATION_STATES::FIGHTING_1)
	{
		currentFrame.top = 128.f;
		if (animationTimer.getElapsedTime().asSeconds() >= 0.05f)
		{
			animations();
		}
	}
	else if (animState == PLAYER_ANIMATION_STATES::FIGHTING_1_RUN)
	{
		currentFrame.top = 96.f;
		if (animationTimer.getElapsedTime().asSeconds() >= 0.05f)
		{
			animations();
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

void Player::animations()
{
	currentFrame.left += 16.f;
	if (currentFrame.left >= 63.f || currentFrame.left <= 0.f)
		currentFrame.left = 0.f;

	animationTimer.restart();
	sprite.setTextureRect(currentFrame);
}

const int& Player::getHp() const
{
	return Hp;
}

const int& Player::getMaxHp() const
{
	return MaxHp;
}

const float& Player::getDirection() const
{
	return sprite.getScale().x;
}

void Player::setHp(const int& hp)
{
	Hp += hp;

	if (Hp > MaxHp)
	{
		Hp = MaxHp;
	}
}

void Player::update(Map* map, bool& newMap)
{
	upedateAttack(attackCooldown, 0.03f);
	if(isWeapon[2])
		upedateAttack(attackCooldownBullet, 0.01f);
	updateMovement(map, newMap);
	updateAnimState(velocity);
	updateAnimations();
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(sprite);
}

