#pragma once
#include "Enemy.h"
#include "Ghost.h"

class Boss : public Enemy
{
private:
	sf::Vector2i startPosition;
	sf::Vector2i goToPosition;

	bool isGoToPosition;
	bool isStartPosition;

	std::vector<std::pair<int, bool>> attakPair;
	sf::Clock canAttack;
	int attackNumber;

	void updateMove(const sf::Vector2f& playerPosition) override;
	void updateAttack(const sf::Vector2f& playerPosition, std::vector<BossBullet*>& bossBullets, std::vector<Enemy*>& enemies);

	void goTo(sf::Vector2i position);
	void goToStartPosition();
	void attack_1();
	void attack_2(std::vector<BossBullet*>& bossBullets);
	void attack_3(std::vector<Enemy*>& enemies);

public:
	Boss(const float& x, const float& y);
	~Boss();

	void update(const sf::Vector2f& playerPosition, std::vector<BossBullet*>& bossBullets, std::vector<Enemy*>& enemies) override;
};

