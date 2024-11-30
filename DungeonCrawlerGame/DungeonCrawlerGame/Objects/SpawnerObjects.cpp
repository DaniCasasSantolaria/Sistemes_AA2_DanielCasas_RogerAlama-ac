#include "SpawnerObjects.h"

void SpawnerObjects::SpawnLoop(NodeMap* currentMap, int mapNumber, int cooldown) {
	while (spawning) {
		SpawnObject(currentMap, mapNumber);
		std::this_thread::sleep_for(std::chrono::milliseconds(cooldown));
	}
}

Object* SpawnerObjects::SpawnObject(NodeMap* currentMap, int numberMap) {
	Object* object = new Object(new Node(Vector2(currentMap->GetOffset().x, currentMap->GetOffset().y), new INodeContent(NodeContent::INVALID)), numberMap);
	bool isEmpty = false;
	while (!isEmpty) {
		Vector2 randomPosition;
		randomPosition.x = (rand() % (currentMap->GetSize().x)) + currentMap->GetOffset().x;
		randomPosition.y = (rand() % (currentMap->GetSize().y)) + currentMap->GetOffset().y;
		currentMap->SafePickNode(randomPosition, [&isEmpty, &object, randomPosition, numberMap](Node* auxNode) {
			if (auxNode->GetINodeContent()->GetContent() == NodeContent::NOTHING) {
				int random = (rand() % 2);
				NodeContent content;
				if(random == 0)
					content = NodeContent::POTION;
				else
					content = NodeContent::COIN;

				Node* node = new Node(randomPosition, new INodeContent(content));
				object = new Object(node, numberMap);
				auxNode->SetContent(content);
				auxNode->DrawContent(randomPosition);
				isEmpty = true;
			}
			});
	}
	return object;
};