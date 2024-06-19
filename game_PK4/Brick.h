#pragma once

#ifndef BRICK_H
#define BRICK_H

#include "Block.h"
#include "Player.h"

class Brick : public Block
{
public:
	Brick(const float& x, const float& y);
	void isIntersectsX(sf::Sprite& sprite, sf::Vector2f& velocity, bool& newMap, sf::Vector2f& beforeJump) override;
	void isIntersectsY(sf::Sprite& sprite, sf::Vector2f& velocity, bool& newMap, bool& canJump, sf::Vector2f& beforeJump) override;
};
#endif 