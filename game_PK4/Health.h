#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <iostream>

class Health
{
private:
	int addHp;

	sf::Texture texture;
	sf::Sprite sprite;

public:
	Health(const float& x, const float& y);
	~Health();

	const sf::FloatRect& getGlobalBounds() const;
	const int& getAddHp() const;

	void render(sf::RenderTarget* target);
};

