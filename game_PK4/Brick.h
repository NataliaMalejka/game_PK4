#pragma once

#ifndef BRICK_H
#define BRICK_H

#include "Player.h"

class Brick
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	bool teleport;

public:
	Brick(const std::string& fileName, float x, float y, bool t);
	virtual ~Brick();
	const bool getTeleport();

	const sf::FloatRect getGlobalBounds() const;

	void render(sf::RenderTarget* target);
};

#endif