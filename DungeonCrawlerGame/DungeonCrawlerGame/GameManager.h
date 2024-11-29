#pragma once
#include "Player/Player.h"
#include "Enemies/Enemy.h"
#include "Nodes/NodeMap.h"
#include "dist/json/json.h"
#include "Objects/Object.h"
#include "Objects/Chest.h"
#include "Timer/Timer.h"
#include "Nodes/WorldMap.h"

class GameManager {
private:
	Player* player;
	WorldMap* worldMap;

	//NodeMap* currentMap;
	//std::vector<NodeMap*> maps;
	//std::vector<Object*> objects;
	//std::vector<Enemy*> enemies;
	//std::vector<Chest*> chests;
	int currentMapNumber = 4;
public:
	GameManager();
	Json::Value CodeEnemies();
	Json::Value CodeMaps();
	void Code();
	void Decode();
	void PrintNewMap();
	void Print();
	void Start();
	void Update();
	void End();
	~GameManager();
};