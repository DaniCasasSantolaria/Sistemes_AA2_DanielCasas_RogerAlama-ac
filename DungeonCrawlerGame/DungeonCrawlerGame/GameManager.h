#pragma once
#include "Player/Player.h"
#include "Enemies/Enemy.h"
#include "Nodes/NodeMap.h"
#include "dist/json/json.h"
#include "Objects/Object.h"
#include "Objects/Chest.h"
#include "Timer/Timer.h"

class GameManager {
private:
	Player* player;
	std::vector<Enemy*> enemies;
	std::vector<NodeMap*> maps;
	NodeMap* currentMap;
	int currentMapNumber = 4;
	std::vector<Object*> objects;
	std::vector<Chest*> chests;
public:
	GameManager();
	Json::Value CodeEnemies();
	Json::Value CodeMaps();
	void Code();
	void Decode();
	void PrintNewMap();
	void CheckPortals();
	void Print();
	void Start();
	void Update();
	void End();
	~GameManager();
};