#pragma once
#include "Chest.h"
#include "Object.h"
class SpawnerChests {
public:
	SpawnerChests() = default;
	void SpawnChest(Vector2 position) { 
		ObjectType random = static_cast<ObjectType> (rand() % 2);
		Node* node = new Node(position, new INodeContent(NodeContent::CHEST)); 
		Object* object = new Object(random, node);
		Chest* chest = new Chest(object, node);
	}
};