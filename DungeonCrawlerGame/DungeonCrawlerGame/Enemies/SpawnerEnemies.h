#pragma once
#include "Enemy.h"

class SpawnerEnemies {
private:
	bool spawning = true;

	void SpawnLoop(NodeMap* currentMap, int mapNumber, bool hasToDraw, int spawnIntervalMs);
public:
	SpawnerEnemies() = default;

	inline void StartSpawning(NodeMap* currentMap, int mapNumber, bool hasToDraw, int cooldown) {
		spawning = true;
		std::thread* spawnThread = new std::thread(&SpawnerEnemies::SpawnLoop, this, currentMap, mapNumber, hasToDraw, cooldown);
	}

	inline void StopSpawning() {
		spawning = false;
	}

	static Enemy* SpawnEnemy(NodeMap* currentMap, int mapNumber, bool hasToDraw);
};