#pragma once
#include "Chest.h"
#include "Object.h"
class SpawnerChests {
public:
	SpawnerChests() = default;
	static Chest* SpawnChest(NodeMap* currentMap);
};
