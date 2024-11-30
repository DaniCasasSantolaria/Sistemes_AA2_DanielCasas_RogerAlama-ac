#include "WorldMap.h"
#include "../Enemies/SpawnerEnemies.h"
#include "../Objects/SpawnerObjects.h"
#include "../Objects/SpawnerChests.h"
#include "../ConsoleControl/ConsoleControl.h"
#include <iostream>

void WorldMap::PrintCurrentMap(NodeMap* currentMap) {
    CC::Lock();
    CC::SetPosition(0, 0);
    CC::Unlock();
    _currentMap->Draw();
}

void WorldMap::PrintNewMap(NodeMap* newMap){ 
    system("cls");
    newMap->Draw();
}

void WorldMap::SetMap() {
    int numMap = 0;
    for (int i = 0; i < 33; i += 11) {
        for (int j = 0; j < 33; j += 11) {
            NodeMap* map = new NodeMap(Vector2(11, 11), Vector2(j, i));
            map->CreatePortals(numMap);
            _maps.push_back(map);
            numMap++;
        }
    }
    currentMapNumber = 4;
    _currentMap = _maps[currentMapNumber];
    player = new Player(_currentMap);
    _currentMap->SafePickNode(player->GetPosition(), [this](Node* auxNode) {
        auxNode->SetContent(NodeContent::PLAYER);
        });
    bool hasToDraw = false;
    for (int i = 0; i < 9; i++) {
        if (currentMapNumber == i)
            hasToDraw = true;
        _enemies.push_back(SpawnerEnemies::SpawnEnemy(_maps[i], i, hasToDraw));
        _enemies.push_back(SpawnerEnemies::SpawnEnemy(_maps[i], i, hasToDraw));

        _objects.push_back(SpawnerObjects::SpawnObject(_maps[i], i));
        _objects.push_back(SpawnerObjects::SpawnObject(_maps[i], i));

        _chests.push_back(SpawnerChests::SpawnChest(_maps[i], i));
        _chests.push_back(SpawnerChests::SpawnChest(_maps[i], i));
        hasToDraw = false;
    }

    for (Enemy* e : _enemies) {
        Vector2 pos = e->GetPosition();
        if (e->GetMap() == currentMapNumber) {
            _currentMap->SafePickNode(pos, [this, pos](Node* auxNode) {
                auxNode->SetContent(NodeContent::ENEMY);
            });
        }
    }
    for (Object* o : _objects) {
        Vector2 pos = o->GetNode()->GetPosition();
        if (o->GetMap() == currentMapNumber) {
            _currentMap->SafePickNode(pos, [this, o](Node* auxNode) {
                auxNode->SetContent(o->GetNode()->GetContent()->GetContent());
            });
        }
    }
    for (Chest* c : _chests) {
        Vector2 pos = c->GetNode()->GetPosition();
        if (c->GetMap() == currentMapNumber) {
            _currentMap->SafePickNode(pos, [this, c](Node* auxNode) {
                auxNode->SetContent(c->GetNode()->GetContent()->GetContent());
            });
        }
    }
}
