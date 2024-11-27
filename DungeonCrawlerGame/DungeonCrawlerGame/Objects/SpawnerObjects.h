#pragma once
#include "../Nodes/NodeMap.h"
#include "Object.h"
#include "../Enemies/Enemy.h"
class SpawnerObjects
{

public:
	SpawnerObjects() = default;
	static Object* SpawnObject(NodeMap* currentMap);
};

