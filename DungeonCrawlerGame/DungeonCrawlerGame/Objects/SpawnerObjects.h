#pragma once
#include "../Nodes/NodeMap.h"
#include "Object.h"
#include "../Enemies/Enemy.h"
class SpawnerObjects
{
private:
	Vector2 position;
	ObjectType objectType;
	Object* object;
public:
	SpawnerObjects(Vector2 pos, ObjectType oType) : position(pos), objectType(oType) {}
	void SpawnObject(Node* node);
};

