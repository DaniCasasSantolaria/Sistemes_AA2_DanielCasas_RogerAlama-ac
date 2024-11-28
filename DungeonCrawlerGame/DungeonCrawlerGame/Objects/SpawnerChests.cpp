#include "SpawnerChests.h"

Chest* SpawnerChests::SpawnChest(NodeMap* currentMap) {
    Chest* chest = new Chest(nullptr, nullptr);
	bool isEmpty = false;
	while (!isEmpty) {
		Vector2 randomPosition{ rand() % 10, rand() % 10 };
		currentMap->SafePickNode(randomPosition, [&isEmpty, chest, randomPosition](Node* auxNode) {
			if (auxNode->GetINodeContent()->GetContent() == NodeContent::NOTHING) {
				NodeContent random = static_cast<NodeContent> (rand() % ((8 - 7 + 1) + 7));
				Node* node = new Node(randomPosition, new INodeContent(NodeContent::CHEST));
				Object* object = new Object(new Node(randomPosition, new INodeContent(random)));
				chest->SetObject(object);
				chest->SetNode(node);
				chest->Draw();
				auxNode->SetContent(NodeContent::CHEST);
				isEmpty = true;
			}
			});
	}
	return chest;
}