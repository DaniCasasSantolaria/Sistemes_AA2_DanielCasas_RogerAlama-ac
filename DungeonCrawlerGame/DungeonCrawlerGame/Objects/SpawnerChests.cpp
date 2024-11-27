#include "SpawnerChests.h"

Chest* SpawnerChests::SpawnChest(NodeMap* currentMap) {
    Chest* chest = new Chest(nullptr, nullptr);
	bool isEmpty = false;
	while (!isEmpty) {
		Vector2 randomPosition{ rand() % 10, rand() % 10 };
		currentMap->SafePickNode(randomPosition, [&isEmpty, chest, randomPosition](Node* auxNode) {
			if (auxNode->GetINodeContent()->GetContent() == NodeContent::NOTHING) {
				ObjectType random = static_cast<ObjectType> (rand() % 2);
				Node* node = new Node(randomPosition, new INodeContent(NodeContent::CHEST));
				Object* object = new Object(random, node);
				chest->SetObject(object);
				chest->SetNode(node);
				chest->Draw();
				isEmpty = true;
			}
			});
	}
	return chest;
}