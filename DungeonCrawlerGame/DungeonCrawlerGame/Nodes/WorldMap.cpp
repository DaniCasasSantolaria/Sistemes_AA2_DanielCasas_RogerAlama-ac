#include "WorldMap.h"
#include "../Enemies/SpawnerEnemies.h"
#include "../Objects/SpawnerObjects.h"
#include "../Objects/SpawnerChests.h"
#include <iostream>

void WorldMap::PrintCurrentMap(NodeMap* currentMap)
{
	_gridMutex.lock();
	for (NodeMap::NodeColumn* column : _currentMap->GetNodeGrid(currentMap)) {
		for (Node* node : *column) {
			node->Lock();
			node->DrawContent(node->GetPosition());
			node->Unlock();
		}
		std::cout << std::endl;
	}
	_gridMutex.unlock();
}

void WorldMap::SetMap()
{
    srand(time(NULL));
    int positionX = rand() % (9 - 1 + 1) + 1;
    int positionY = rand() % (9 - 1 + 1) + 1;
    player = new Player();
    for (int i = -10; i < 30; i += 10) {
        for (int j = -10; j < 30; j += 10)
            _maps.push_back(new NodeMap(Vector2(11, 11), Vector2(j, i)));
    }
    currentMapNumber = 4;
    _currentMap = _maps[currentMapNumber];
    _currentMap->SafePickNode(player->GetPosition(), [this](Node* auxNode) {
        auxNode->SetContent(NodeContent::PLAYER);
        });
    _enemies.push_back(SpawnerEnemies::SpawnEnemy(_currentMap));
    _enemies.push_back(SpawnerEnemies::SpawnEnemy(_currentMap));

    _objects.push_back(SpawnerObjects::SpawnObject(_currentMap));
    _objects.push_back(SpawnerObjects::SpawnObject(_currentMap));

    _chests.push_back(SpawnerChests::SpawnChest(_currentMap));
    _chests.push_back(SpawnerChests::SpawnChest(_currentMap));

    for (Enemy* e : _enemies) {
        Vector2 pos = e->GetPosition();
        _currentMap->SafePickNode(pos, [this, pos](Node* auxNode) {
            auxNode->SetContent(NodeContent::ENEMY);
            });
    }
    for (Object* o : _objects) {
        Vector2 pos = o->GetNode()->GetPosition();
        _currentMap->SafePickNode(pos, [this, o](Node* auxNode) {
            auxNode->SetContent(o->GetNode()->GetContent()->GetContent());
            });
    }
    for (Chest* c : _chests) {
        Vector2 pos = c->GetNode()->GetPosition();
        _currentMap->SafePickNode(pos, [this, c](Node* auxNode) {
            auxNode->SetContent(c->GetNode()->GetContent()->GetContent());
            });
    }
}
