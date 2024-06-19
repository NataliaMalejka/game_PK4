#pragma once
#include "Block.h"

class Teleport : public Block
{
public:
	Teleport(const float& x, const float& y);
	void isIntersectsX(sf::Sprite& sprite, sf::Vector2f& velocity, bool& newMap, sf::Vector2f& beforeJump) override;
	void isIntersectsY(sf::Sprite& sprite, sf::Vector2f& velocity, bool& newMap, bool& canJump, sf::Vector2f& beforeJump) override;
};

