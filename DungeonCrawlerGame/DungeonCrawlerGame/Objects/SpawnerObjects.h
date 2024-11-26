#pragma once
#include "../Nodes/NodeMap.h"
#include "Object.h"
#include "../Enemies/Enemy.h"
class SpawnerObjects
{

public:
	SpawnerObjects() = default;
	Object* SpawnObject(Vector2 position) {
		ObjectType random = static_cast<ObjectType> (rand() % 2);
		Node* node = new Node(position, new INodeContent(NodeContent::OBJECT));
		Object* object = new Object(random, node);
		return object;
	};
};

