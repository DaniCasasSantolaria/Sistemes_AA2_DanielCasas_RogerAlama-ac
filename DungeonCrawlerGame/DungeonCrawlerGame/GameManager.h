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
	WorldMap* worldMap;
	int currentMapNumber = 4;
public:
	GameManager();
	Json::Value CodeEnemies();
	Json::Value CodeMaps();
	void Code();
	void Decode();
	void PrintNewMap();
	void PrintStats();
	void Start();
	void Update();
	void End();
	~GameManager();
};