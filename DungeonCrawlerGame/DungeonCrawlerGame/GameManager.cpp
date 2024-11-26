#include "GameManager.h"
#include "../InputManager/InputManager.h"
#include "Timer/Timer.h"

GameManager::GameManager() {
    player = new Player();
    for (int i = -10; i < 30; i += 10) {
        for(int j = -10; j < 30; j += 10)
            maps.push_back(new NodeMap(Vector2(11, 11), Vector2(j, i)));
    }
    currentMap = maps[4];
}
void GameManager::PrintNewMap() {
    currentMap->Draw();
}

void GameManager::Print() {
    player->Draw();
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