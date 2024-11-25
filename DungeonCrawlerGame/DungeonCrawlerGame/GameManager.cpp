#include "GameManager.h"
#include "../InputManager/InputManager.h"
#include <fstream>
#include <iostream>

GameManager::GameManager() {
    player = new Player();
    for (int i = -10; i < 30; i += 10) {
        for(int j = -10; j < 30; j += 10)
            maps.push_back(new NodeMap(Vector2(10, 10), Vector2(j, i)));
    }
    enemies.push_back(new Enemy());
    currentMap = maps[4];
    maps[0]->Draw();
}

Json::Value GameManager::CodeEnemies() {
    Json::Value json = Json::Value();
    Json::Value enemiesArray(Json::arrayValue);
    for (Enemy* enemy : enemies)
        enemiesArray.append(enemy->Code());
    json["enemies"] = enemiesArray;
    return json;
}

Json::Value GameManager::CodeMaps() {
    Json::Value json = Json::Value();
    Json::Value mapsArray(Json::arrayValue);
    for (NodeMap* map : maps)
        mapsArray.append(map->Code());
    json["grids"] = mapsArray;
    return json;
}

void GameManager::Code() {
    Json::Value jsonArray = Json::Value(Json::arrayValue);
    jsonArray.append(player->Code());
    jsonArray.append(CodeEnemies());
    jsonArray.append(CodeMaps());
    jsonArray.append(currentMap->Code());

    try {
        std::ofstream jsonWriteFile = std::ofstream("DungeonCrawlerGame.json", std::ifstream::binary);

        if (!jsonWriteFile.fail()) {
            jsonWriteFile << jsonArray;
            jsonWriteFile.close();
        }
        else {
            throw std::exception("ERROR AL ABRIR EL ARCHIVO JSON");
        }
    }
    catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }
}

void GameManager::Decode() {
    std::ifstream jsonReadFile = std::ifstream("DungeonCrawlerGame.json", std::ifstream::binary);

    if (!jsonReadFile.fail()) {
        Json::Value readedJson;
        jsonReadFile >> readedJson;

        if (readedJson[0].isMember("player")) {
            player->Decode(readedJson[0]["player"]);
        }

        if (readedJson[1].isMember("enemies")) {
            for (Json::Value value : readedJson[1]["enemies"]) {
                Enemy* e = new Enemy();
                e->Decode(value["enemy"]);
                enemies.push_back(e);
            }
        }

        if (readedJson[2].isMember("grids")) {
            for (Json::Value value : readedJson[2]["grids"]) {
                NodeMap* m = new NodeMap(Vector2(11,11), Vector2(0 ,0));
                m->Decode(value["grid"]);
                maps.push_back(m);
            }
        }

        if (readedJson[3].isMember("currentMap")) {
            currentMap->Decode(readedJson["currentMap"]);
        }

        jsonReadFile.close();
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