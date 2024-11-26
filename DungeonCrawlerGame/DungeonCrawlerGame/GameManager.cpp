#include "GameManager.h"
#include "../InputManager/InputManager.h"
#include "Timer/Timer.h"

GameManager::GameManager() {
    srand(time(NULL));
    int positionX = rand() % (9 - 1 + 1) + 1;
    int positionY = rand() % (9 - 1 + 1) + 1;
    player = new Player();
    object = new Object(ObjectType::POTION, new Node(Vector2(positionX,positionY), new INodeContent(NodeContent::OBJECT)));
    objects.push_back(object);
    for (int i = -10; i < 30; i += 10) {
        for(int j = -10; j < 30; j += 10)
            maps.push_back(new NodeMap(Vector2(11, 11), Vector2(j, i)));
    }
    currentMapNumber = 4;
    currentMap = maps[currentMapNumber];
}
void GameManager::PrintNewMap() {
    system("cls");
    currentMap->Draw();
}

void GameManager::CheckPortals() {
    if (player->GetPosition().x == 0 && player->GetPosition().y == currentMap->GetSize().y / 2
        && currentMapNumber > 2) {
        currentMapNumber -= 3;
        currentMap = maps[currentMapNumber];
    }
    /*else if(player->GetPosition().x == currentMap->GetSize().x / 2 && player->GetPosition().y == currentMap->GetSize().y
        && currentMapNumber > 2)*/
}

void GameManager::Print() {
    player->Draw();
    for (Object* object : objects) {
        object->PrintObject();
    }
    /*for(Enemy* e : enemies)*/
}
void GameManager::Start() {
    player->ActivatePlayer();
}

void GameManager::Update() {
    Print();
    std::thread* move = new std::thread(Timer::DelayExecute, player->GetCooldownMovement(), [this]() {
        player->UpdatePosition();
        });
    move->detach();
    /*for (Enemy* e : enemies)
        e->Update();*/
}

void GameManager::End() {
    player->DesactivatePlayer();
}

GameManager::~GameManager() {
    delete player;
    for (Enemy* e : enemies)
        delete e;
    for (NodeMap* map : maps)
        delete map;
    delete currentMap;
}