#pragma once
#include "../Nodes/NodeMap.h"
#include "Object.h"
#include "../Enemies/Enemy.h"
class SpawnerObjects {
private:
    bool spawning = true;

    void SpawnLoop(NodeMap* currentMap, int mapNumber, int cooldown);
public:
	SpawnerObjects() = default;
    inline void StartSpawning(NodeMap* currentMap, int mapNumber, int cooldown) {
        spawning = true;
        std::thread* spawnThread = new std::thread(&SpawnerObjects::SpawnLoop, this, currentMap, mapNumber, cooldown);
    }

    inline void StopSpawning() {
        if (spawning) {
            spawning = false;
        }
    }
	static Object* SpawnObject(NodeMap* currentMap, int numberMap);
};

