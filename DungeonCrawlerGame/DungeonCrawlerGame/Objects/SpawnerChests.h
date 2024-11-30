#pragma once
#include "Chest.h"
#include "Object.h"

class SpawnerChests {
private:
    bool spawning;
    void SpawnLoop(NodeMap* currentMap, int mapNumber, int cooldown) {
        while (spawning) {
            SpawnChest(currentMap, mapNumber);
            std::this_thread::sleep_for(std::chrono::milliseconds(cooldown));
        }
    }
public:
	SpawnerChests() = default;
    inline void StartSpawning(NodeMap* currentMap, int mapNumber, int cooldown) {
        spawning = true;
        std::thread* spawnThread = new std::thread(&SpawnerChests::SpawnLoop, this, currentMap, mapNumber, cooldown);
    }

    inline void StopSpawning() {
        if (spawning) {
            spawning = false;
        }
    }
	static Chest* SpawnChest(NodeMap* currentMap, int currentMapNumber);
};
