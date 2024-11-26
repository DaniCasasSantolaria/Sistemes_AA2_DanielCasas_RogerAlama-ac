#include "GameManager.h"
#include "../InputManager/InputManager.h"
#include "Timer/Timer.h"
#include "ConsoleControl/ConsoleControl.h"

GameManager::GameManager() {
    srand(time(NULL));
    int positionX = rand() % (9 - 1 + 1) + 1;
    int positionY = rand() % (9 - 1 + 1) + 1;
    player = new Player();
    object = new Object(ObjectType::POTION, new Node(Vector2(positionX,positionY), new INodeContent(NodeContent::OBJECT)));
    objects.push_back(object);
    for (int i = -10; i < 30; i += 10) {
        for (int j = -10; j < 30; j += 10)
            maps.push_back(new NodeMap(Vector2(11, 11), Vector2(j, i)));
    }
    currentMapNumber = 4;
    currentMap = maps[currentMapNumber];

    enemies.push_back(spawnerEnemies->SpawnEnemy(currentMap));
}
void GameManager::PrintNewMap() {
    system("cls");
    currentMap->Draw();
}

void GameManager::CheckPortals() {
    Vector2 pos = player->GetPosition();
    int nextMap = 0;
    switch (player->GetPlayerState()) {
    case Player::PlayerState::DOWN:
        nextMap = 3;
        pos += Vector2(0, 1);
        break;
    case Player::PlayerState::LEFT:
        nextMap = -1;
        pos += Vector2(-1, 0);
        break;
    case Player::PlayerState::RIGHT:
        nextMap = 1;
        pos += Vector2(1, 0);
        break;
    case Player::PlayerState::UP:
        nextMap = -3;
        pos += Vector2(0, -1);
        break;
    }
    currentMap->SafePickNode(pos, [this, nextMap](Node* node) {
        if (node->GetINodeContent()->GetContent() == NodeContent::PORTAL) {
            if(currentMapNumber + nextMap >= 0 && currentMapNumber + nextMap < 9)
                currentMap = maps[currentMapNumber + nextMap];
            //Falta asignar els portals correctament als mapas
        }
        });
}

void GameManager::Print() {
    player->Draw();
    for (Object* object : objects) {
        object->PrintObject();
    }
    for(Enemy* e : enemies){
        e->Draw();
    }
    CC::Lock();
    CC::SetPosition(currentMap->GetSize().x, currentMap->GetSize().y);
    CC::Unlock();
}
void GameManager::Start() {
    player->ActivatePlayer();
    Print();
}

void GameManager::Update() {
    /*std::thread* move = new std::thread(Timer::DelayExecute, player->GetCooldownMovement(), [this]() {*/
        player->UpdatePosition();
        /*});
    move->detach();*/
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