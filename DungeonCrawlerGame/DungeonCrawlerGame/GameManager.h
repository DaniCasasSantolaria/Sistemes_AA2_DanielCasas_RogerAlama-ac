#pragma once
#include "Player/Player.h"
#include "Enemies/Enemy.h"
#include "Nodes/NodeMap.h"

class GameManager {
private:
	Player* player;
	std::vector<Enemy*> enemies;
	std::vector<NodeMap*> maps;
	NodeMap* currentMap;
public:
	GameManager();
	void PrintNewMap();
	void Print();
	void Start();
	void Update();
	void End();
	~GameManager();
};