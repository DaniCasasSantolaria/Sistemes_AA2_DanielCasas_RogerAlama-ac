#pragma once
#include "Player/Player.h"
#include "Enemies/Enemy.h"
#include "Nodes/NodeMap.h"
#include "Objects/Object.h"

class GameManager {
private:
	Player* player;
	std::vector<Enemy*> enemies;
	std::vector<NodeMap*> maps;
	NodeMap* currentMap;
	std::vector<Object*> objects;
	Object* object;
public:
	GameManager();
	void Start();
	void Update(float dt);
	void End();
	~GameManager();
};