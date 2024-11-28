#include "SpawnerObjects.h"

Object* SpawnerObjects::SpawnObject(NodeMap* currentMap)
{
	Object* object = new Object(new Node(Vector2(0, 0), new INodeContent(NodeContent::INVALID)));
	bool isEmpty = false;
	while (!isEmpty) {
		Vector2 randomPosition{ rand() % (10 - 1 + 1 ) + 1,rand() % (10 - 1 + 1) + 1 };
		currentMap->SafePickNode(randomPosition, [&isEmpty, object, randomPosition](Node* auxNode) {
			if (auxNode->GetINodeContent()->GetContent() == NodeContent::NOTHING) {
				int random = (rand() % 2);
				NodeContent content;
				if(random == 0)
					content = NodeContent::POTION;
				else
					content = NodeContent::COIN;

				Node* node = new Node(randomPosition, new INodeContent(content));
				Object* object = new Object(node);
				auxNode->SetContent(content);
				auxNode->DrawContent();
				isEmpty = true;
			}
			});
	}
	return object;
};
