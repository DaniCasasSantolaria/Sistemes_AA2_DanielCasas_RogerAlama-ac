#pragma once
#include "Player/Player.h"
#include "Enemies/Enemy.h"
#include "Nodes/NodeMap.h"

class GameManager {
private:
	Player* player;
	std::vector<Enemy*> enemies;
	NodeMap* map;
	bool enemyIsDead;
public:
	GameManager();
	void Start();
	void Update(float dt);
	void End();
	~GameManager();
};