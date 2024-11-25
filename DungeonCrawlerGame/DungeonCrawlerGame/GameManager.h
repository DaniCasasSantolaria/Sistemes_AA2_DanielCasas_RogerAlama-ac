#pragma once
#include "Player/Player.h"
#include "Enemies/Enemy.h"
#include "Nodes/NodeMap.h"
#include "dist/json/json.h"

class GameManager {
private:
	Player* player;
	std::vector<Enemy*> enemies;
	std::vector<NodeMap*> maps;
	NodeMap* currentMap;
public:
	GameManager();
	Json::Value CodeEnemies();
	Json::Value CodeMaps();
	void Code();
	void Decode();
	void Start();
	void Update(float dt);
	void End();
	~GameManager();
};