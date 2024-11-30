#include "SpawnerEnemies.h"

void SpawnerEnemies::SpawnLoop(NodeMap* currentMap, int mapNumber, bool hasToDraw, int spawnIntervalMs) {
	while (spawning) {
		SpawnEnemy(currentMap, mapNumber, hasToDraw);
		std::this_thread::sleep_for(std::chrono::milliseconds(spawnIntervalMs));
	}
}

Enemy* SpawnerEnemies::SpawnEnemy(NodeMap* currentMap, int mapNumber, bool hasToDraw) {
	Enemy* enemy = new Enemy(1, 5, Vector2(currentMap->GetOffset().x, currentMap->GetOffset().y), currentMap, mapNumber);
	bool isEmpty = false;
	while (!isEmpty) {
		Vector2 randomPosition;
		randomPosition.x = (rand() % (currentMap->GetSize().x)) + currentMap->GetOffset().x;
		randomPosition.y = (rand() % (currentMap->GetSize().y)) + currentMap->GetOffset().y;
		currentMap->SafePickNode(randomPosition, [&isEmpty, enemy, randomPosition, hasToDraw](Node* auxNode) {
			if (auxNode->GetINodeContent()->GetContent() == NodeContent::NOTHING) {
				enemy->SetPosition(randomPosition);
				if (hasToDraw)
					enemy->Draw();
				auxNode->SetContent(NodeContent::ENEMY);
				isEmpty = true;
			}
			});
	}
	return enemy;
}
