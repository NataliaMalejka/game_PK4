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

	sf::Music soundsBlaster;

	std::vector<Enemy*>* enemies_;

	void updateMove(const sf::Vector2f& playerPosition) override;
	void updateAttack(const sf::Vector2f& playerPosition, std::vector<BossBullet*>& bossBullets);

	void goTo(sf::Vector2i position);
	void goToStartPosition();
	void attack_1();
	void attack_2(std::vector<BossBullet*>& bossBullets);
	void attack_3();

public:
	Boss(const float& x, const float& y, std::vector<Enemy*>* enemies);
	~Boss();

	void update(const sf::Vector2f& playerPosition, std::vector<BossBullet*>& bossBullets) override;
};

