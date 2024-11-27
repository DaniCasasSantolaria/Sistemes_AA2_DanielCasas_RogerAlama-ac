#include "SpawnerObjects.h"

Object* SpawnerObjects::SpawnObject(NodeMap* currentMap)
{
	Object* object = new Object(ObjectType::COIN, new Node(Vector2(0, 0), new INodeContent(NodeContent::INVALID)));
	bool isEmpty = false;
	while (!isEmpty) {
		Vector2 randomPosition{ rand() % (10 - 1 + 1 ) + 1,rand() % (10 - 1 + 1) + 1 };
		currentMap->SafePickNode(randomPosition, [&isEmpty, object, randomPosition](Node* auxNode) {
			if (auxNode->GetINodeContent()->GetContent() == NodeContent::NOTHING) {
				ObjectType random = static_cast<ObjectType> (rand() % 2);
				Node* node = new Node(randomPosition, new INodeContent(NodeContent::OBJECT));
				Object* object = new Object(random, node);
				object->Draw();
				object->SetNode(node);
				isEmpty = true;
			}
			});
	}
	return object;
};
