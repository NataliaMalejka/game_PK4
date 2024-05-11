#pragma once
#include "Player.h"

class Brick
{
private:
	sf::Texture texture;
	sf::Sprite sprite;

public:
	Brick(float x, float y);
	virtual ~Brick();

	const sf::FloatRect getGlobalBounds() const;

	void render(sf::RenderTarget* target);
};

