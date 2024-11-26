#pragma once
#include "../Nodes/NodeMap.h"
#include "Object.h"
#include "../Enemies/Enemy.h"
class SpawnerObjects
{

public:
	SpawnerObjects() = default;
	Object* SpawnObject(NodeMap* currentMap) {
		Object* object = new Object(ObjectType::COIN, new Node(Vector2(0,0), new INodeContent(NodeContent::INVALID)));
		bool isEmpty = false;
		while (!isEmpty) {
			Vector2 randomPosition{ rand() % 10, rand() % 10 };
			currentMap->SafePickNode(randomPosition, [this, &isEmpty, object, randomPosition](Node* auxNode) {
				if (auxNode->GetINodeContent()->GetContent() == NodeContent::NOTHING) {
					ObjectType random = static_cast<ObjectType> (rand() % 2);
					Node* node = new Node(randomPosition, new INodeContent(NodeContent::OBJECT));
					Object* object = new Object(random, node);
					object->Draw();
					isEmpty = true;
				}
				});
		}
		return object;
	};
};

