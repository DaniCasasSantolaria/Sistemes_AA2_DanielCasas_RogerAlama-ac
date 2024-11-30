#include "SpawnerChests.h"

Chest* SpawnerChests::SpawnChest(NodeMap* currentMap, int currentMapNumber) {
    Chest* chest = new Chest(nullptr, nullptr, currentMapNumber);
	bool isEmpty = false;
	while (!isEmpty) {
		Vector2 randomPosition;
		randomPosition.x = (rand() % (currentMap->GetSize().x)) + currentMap->GetOffset().x;
		randomPosition.y = (rand() % (currentMap->GetSize().y)) + currentMap->GetOffset().y;
		currentMap->SafePickNode(randomPosition, [&isEmpty, chest, randomPosition, currentMapNumber](Node* auxNode) {
			if (auxNode->GetINodeContent()->GetContent() == NodeContent::NOTHING) {
				NodeContent random = static_cast<NodeContent> (rand() % ((8 - 7 + 1) + 7));
				Node* node = new Node(randomPosition, new INodeContent(NodeContent::CHEST));
				Object* object = new Object(new Node(randomPosition, new INodeContent(random)), currentMapNumber);
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