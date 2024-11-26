#pragma once
#include "Player/Player.h"
#include "Enemies/Enemy.h"
#include "Nodes/NodeMap.h"
#include "Objects/Object.h"
#include "Enemies/SpawnerEnemies.h"

class GameManager {
private:
	Player* player;
	Enemy* enemy;
	std::vector<Enemy*> enemies;
	std::vector<NodeMap*> maps;
	NodeMap* currentMap;
	int currentMapNumber = 4;
	std::vector<Object*> objects;
	Object* object;
	SpawnerEnemies* spawnerEnemies;
public:
	GameManager();
	void PrintNewMap();
	void CheckPortals();
	void Print();
	void Start();
	void Update();
	void End();
	~GameManager();
};