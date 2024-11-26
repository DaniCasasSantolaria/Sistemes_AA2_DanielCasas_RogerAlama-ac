#pragma once
#include "Enemy.h"
class SpawnerEnemies {
public:
	SpawnerEnemies() = default;
	void SpawnEnemy(Vector2 position) {
		Node* node = new Node(position, new INodeContent(NodeContent::ENEMY));
		Enemy* enemy = new Enemy(100, 20);
	}
};