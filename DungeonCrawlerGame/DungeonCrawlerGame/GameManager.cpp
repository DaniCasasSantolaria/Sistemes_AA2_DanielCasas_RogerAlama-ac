#include "GameManager.h"
#include "../InputManager/InputManager.h"
#include "Timer/Timer.h"
#include "ConsoleControl/ConsoleControl.h"
#include "Enemies/SpawnerEnemies.h"
#include "Objects/SpawnerChests.h"
#include "Objects/SpawnerObjects.h"
#include <fstream>
#include <iostream>


GameManager::GameManager() {
    worldMap = new WorldMap();
    worldMap->SetMap();
}

Json::Value GameManager::CodeEnemies() {
    Json::Value json = Json::Value();
    Json::Value enemiesArray(Json::arrayValue);
    for (Enemy* enemy : worldMap->GetEnemies())
        enemiesArray.append(enemy->Code());
    json["enemies"] = enemiesArray;
    return json;
}

Json::Value GameManager::CodeMaps() {
    Json::Value json = Json::Value();
    Json::Value mapsArray(Json::arrayValue);
    for (NodeMap* map : worldMap->GetMaps())
        mapsArray.append(map->Code());
    json["grids"] = mapsArray;
    return json;
}

void GameManager::Code() {
    Json::Value jsonArray = Json::Value(Json::arrayValue);
    jsonArray.append(worldMap->GetPlayer()->Code());
    jsonArray.append(CodeEnemies());
    jsonArray.append(CodeMaps());
    jsonArray.append(worldMap->GetCurrentMap()->Code());

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
            worldMap->GetPlayer()->Decode(readedJson[0]["player"]);
        }

        if (readedJson[1].isMember("enemies")) {
            for (Json::Value value : readedJson[1]["enemies"]) {
                Enemy* e = new Enemy();
                e->Decode(value["enemy"]);
                worldMap->GetEnemies().push_back(e);
            }
        }

        if (readedJson[2].isMember("grids")) {
            for (Json::Value value : readedJson[2]["grids"]) {
                if (value.isMember("grid") && value["grid"].isArray()) {
                    NodeMap* m = new NodeMap(Vector2(11, 11), Vector2(0, 0));
                    m->Decode(value);
                    worldMap->GetMaps().push_back(m);
                }
            }
        }

        if (readedJson[3].isMember("currentMap")) {
            worldMap->GetCurrentMap()->Decode(readedJson["currentMap"]);
        }

        jsonReadFile.close();
    }
}

void GameManager::PrintNewMap() {
    system("cls");
    worldMap->GetCurrentMap()->Draw();
    worldMap->GetPlayer()->Draw();
    for (Object* o : worldMap->GetObjects()) {
        if (o->GetMap() == currentMapNumber) {
            o->Draw();
        }
    }
    for (Chest* c : worldMap->GetChests()) {
        if (c->GetMap() == currentMapNumber) {
            c->Draw();
        }
    }
    for (Enemy* e : worldMap->GetEnemies()) {
        if (e->GetMap() == currentMapNumber) {
            e->Draw();
        }
    }
    PrintStats();
}

void GameManager::PrintStats() {
    std::string weapon = "";
    switch (worldMap->GetPlayer()->GetWeapon()->GetWeaponType()) {
    case WeaponType::SWORD:
        weapon = "espada";
        break;
    case WeaponType::SPEAR:
        weapon = "lanza";
        break;
    default:
        break;
    }
    CC::Lock();
    CC::SetPosition(worldMap->GetCurrentMap()->GetSize().x * 4, 0);
    std::cout << "Monedas: " << worldMap->GetPlayer()->GetCoins();
    CC::SetPosition(worldMap->GetCurrentMap()->GetSize().x * 4, 1);
    std::cout << "Vidas: " << worldMap->GetPlayer()->GetLifes();
    CC::SetPosition(worldMap->GetCurrentMap()->GetSize().x * 4, 2);
    std::cout << "Pociones: " << worldMap->GetPlayer()->GetAmountPotions();
    CC::SetPosition(worldMap->GetCurrentMap()->GetSize().x * 4, 3);
    std::cout << "Arma: " << weapon;
    CC::Unlock();
    CC::Lock();
    CC::SetPosition(0, worldMap->GetCurrentMap()->GetSize().y);
    CC::Unlock();
}

void GameManager::Start() {
    NodeMap* currentMap = worldMap->GetCurrentMap();
    int* currentMapNumberPtr = &currentMapNumber;
    std::vector<NodeMap*> maps = worldMap->GetMaps();
    worldMap->GetPlayer()->ActivatePlayer(currentMap, currentMapNumberPtr, maps, worldMap->GetEnemies());
    worldMap->spawnerEnemies.StartSpawning(worldMap->GetCurrentMap(), currentMapNumber, true, 8000);
    worldMap->spawnerChests.StartSpawning(worldMap->GetCurrentMap(), currentMapNumber, 17000);
}

void GameManager::Update() {
    for (Enemy* e : worldMap->GetEnemies()) {
        Timer::DelayExecute(5000, [this, e]() {
            e->Move(worldMap->GetMaps()[e->GetMap()], worldMap->GetCurrentMapNumber());
        });
    }
}

void GameManager::End() {
    worldMap->GetPlayer()->DesactivatePlayer();
    worldMap->spawnerEnemies.StopSpawning();
    worldMap->spawnerChests.StopSpawning();
}

GameManager::~GameManager() {
    for (Enemy* e : worldMap->GetEnemies())
        delete e;
    for (NodeMap* map : worldMap->GetMaps())
        delete map;
    delete  worldMap->GetCurrentMap();
    for (Object* o : worldMap->GetObjects())
        delete o;
    for (Chest* c : worldMap->GetChests())
        delete c;
}