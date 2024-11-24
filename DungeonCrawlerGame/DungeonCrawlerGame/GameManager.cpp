#include "GameManager.h"
#include "../InputManager/InputManager.h"

GameManager::GameManager() {
    player = new Player();
    for (int i = -10; i < 30; i += 10) {
        for(int j = -10; j < 30; j += 10)
            maps.push_back(new NodeMap(Vector2(10, 10), Vector2(j, i)));
    }
    currentMap = maps[4];
    maps[0]->Draw();
}