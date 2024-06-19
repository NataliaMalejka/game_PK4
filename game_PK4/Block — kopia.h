#pragma once

#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <iostream>

class Block
{
protected:
	sf::Texture texture;
	sf::Sprite sprite;

public:
	virtual ~Block() = default;
	const sf::Vector2f getPositionBlock() const;
	const sf::FloatRect getGlobalBounds() const;
	virtual void isIntersectsX(sf::Sprite& sprite, sf::Vector2f& velocity, bool& newMap, sf::Vector2f& beforeJump) = 0;
	virtual void isIntersectsY(sf::Sprite& sprite, sf::Vector2f& velocity, bool& newMap, bool& canJump, sf::Vector2f& beforeJump) = 0;
	void render(sf::RenderTarget* target);
};

#endif 
