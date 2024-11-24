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

void GameManager::Code() {
    Json::Value jsonArray = Json::Value(Json::arrayValue);
    jsonArray.append(player->Code());
    for(Enemy* enemy : enemies)
        jsonArray.append(enemy->Code());
    for (NodeMap* map : maps)
        jsonArray.append(map->Code());
    jsonArray.append(currentMap->Code());
}

void GameManager::Decode(Json::Value json) {
    player->Decode(json);
    /*for (Json::Value value : readedJson) {
        Enemy* e = ICodable::FromJson<Enemy>(value);
        readWeapons.push_back(e);
    }*/
    /*for (Json::Value value : readedJson) {
       NodeMap* m = ICodable::FromJson<NodeMap>(value);
       readWeapons.push_back(m);
   }*/
    currentMap->Decode(json);
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