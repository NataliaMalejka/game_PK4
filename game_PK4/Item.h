#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <iostream>

class Item
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	int vectorNr;

public:
	Item(const std::string& fileName, const float& x, const float& y, const int& i);
	~Item();

	void getItem(std::vector<bool>& vec) const;

	const sf::FloatRect& getGlobalBounds() const;
	void render(sf::RenderTarget* target);
};

