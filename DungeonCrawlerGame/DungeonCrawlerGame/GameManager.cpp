#include "GameManager.h"
#include "../InputManager/InputManager.h"

GameManager::GameManager() {
    srand(time(NULL));
    int positionX = rand() % (9 - 1 + 1) + 1;
    int positionY = rand() % (9 - 1 + 1) + 1;
    player = new Player();
    object = new Object(ObjectType::POTION, new Node(Vector2(positionX,positionY), new INodeContent(NodeContent::OBJECT)));
    for (int i = -10; i < 30; i += 10) {
        for(int j = -10; j < 30; j += 10)
            maps.push_back(new NodeMap(Vector2(10, 10), Vector2(j, i)));
    }
    currentMap = maps[4];
    maps[0]->Draw();
    for (Object* object : objects) {
        object->PrintObject(Vector2(positionX, positionY));
    }
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