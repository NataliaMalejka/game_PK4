#pragma once
#include "Enemy.h"

class Shadow :  public Enemy
{
private:
	sf::Vector2f startPosition;
	void updateMove(const sf::Vector2f& playerPosition) override;

public:
	Shadow(const float& x, const float& y);
	~Shadow();

	void update(const sf::Vector2f& playerPosition, std::vector<BossBullet*>& bossBullets) override;
};

