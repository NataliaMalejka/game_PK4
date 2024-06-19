#pragma once
#include "Enemy.h"

class Ghost :  public Enemy
{
private:
	void updateMove(const sf::Vector2f& playerPosition) override;

public:
	Ghost(const float& x, const float& y);
	~Ghost();

	void update(const sf::Vector2f& playerPosition, std::vector<BossBullet*>& bossBullets, std::vector<Enemy*>& enemies) override;
};

