#include "GameManager.h"
#include "../InputManager/InputManager.h"

GameManager::GameManager() {
    player = new Player();
    enemies.resize(0);
    map = new NodeMap(Vector2(10,10), Vector2(/*OFFSET*/));
}

void GameManager::Update(float dt)
{
 /* for (Enemy* e : enemies) {
        e->GetIfIsDead();
        if (e->SetIfIsDead(enemyIsDead)) {
            LeaveObject();
            delete e;
        }
    }*/
}
