#pragma once
#include "Block.h"

class Spikes : public Block
{
public:
	Spikes(const float& x, const float& y);
	void isIntersectsX(sf::Sprite& sprite, sf::Vector2f& velocity, bool& newMap, sf::Vector2f& beforeJump) override;
	void isIntersectsY(sf::Sprite& sprite, sf::Vector2f& velocity, bool& newMap, bool& canJump, sf::Vector2f& beforeJump) override;
};

