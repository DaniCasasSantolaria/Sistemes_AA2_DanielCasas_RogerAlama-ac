#pragma once
#include "Enemy.h"
class SpawnerEnemies {
public:
	SpawnerEnemies() = default;
	Enemy* SpawnEnemy(NodeMap* currentMap) {
		Enemy* enemy = new Enemy(100, 20, Vector2(0, 0));
		bool isEmpty = false;
		while (!isEmpty) {
			Vector2 randomPosition{ rand() % 10, rand() % 10 };
			currentMap->SafePickNode(randomPosition, [this, &isEmpty, enemy, randomPosition](Node* auxNode) {
				if (auxNode->GetINodeContent()->GetContent() == NodeContent::NOTHING) {
					enemy->SetPosition(randomPosition);
					enemy->Draw();
					isEmpty = true;
				}
				});
		}
		return enemy;
	}
};