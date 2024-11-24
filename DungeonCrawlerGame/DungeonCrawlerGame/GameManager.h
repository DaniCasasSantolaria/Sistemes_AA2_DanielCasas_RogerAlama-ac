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
	void Code();
	void Decode(Json::Value json);
	void Start();
	void Update(float dt);
	void End();
	~GameManager();
};