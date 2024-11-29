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
    srand(time(NULL));
    int positionX = rand() % (9 - 1 + 1) + 1;
    int positionY = rand() % (9 - 1 + 1) + 1;
    player = new Player();
    for (int i = -10; i < 30; i += 10) {
        for (int j = -10; j < 30; j += 10)
            maps.push_back(new NodeMap(Vector2(11, 11), Vector2(j, i)));
    }
    currentMapNumber = 4;
    currentMap = maps[currentMapNumber];
    currentMap->SafePickNode(player->GetPosition(), [this](Node* auxNode){
        auxNode->SetContent(NodeContent::PLAYER);
    });
    enemies.push_back(SpawnerEnemies::SpawnEnemy(currentMap));
    enemies.push_back(SpawnerEnemies::SpawnEnemy(currentMap));

    objects.push_back(SpawnerObjects::SpawnObject(currentMap));
    objects.push_back(SpawnerObjects::SpawnObject(currentMap));

    chests.push_back(SpawnerChests::SpawnChest(currentMap));
    chests.push_back(SpawnerChests::SpawnChest(currentMap));

    for(Enemy* e : enemies){
        Vector2 pos = e->GetPosition();
        currentMap->SafePickNode(pos, [this, pos](Node* auxNode) {
            auxNode->SetContent(NodeContent::ENEMY);
			});
    }
    for(Object* o : objects){
        Vector2 pos = o->GetNode()->GetPosition();
        currentMap->SafePickNode(pos, [this, o](Node* auxNode) {
            auxNode->SetContent(o->GetNode()->GetContent()->GetContent());
			});
    }
    for(Chest* c : chests){
        Vector2 pos = c->GetNode()->GetPosition();
        currentMap->SafePickNode(pos, [this, c](Node* auxNode) {
            auxNode->SetContent(c->GetNode()->GetContent()->GetContent());
			});
    }
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
                Enemy* e = new Enemy(0, 0, Vector2(0,0), nullptr);
                e->Decode(value["enemy"]);
                enemies.push_back(e);
            }
        }

        if (readedJson[2].isMember("grids")) {
            for (Json::Value value : readedJson[2]["grids"]) {
                if (value.isMember("grid") && value["grid"].isArray()) {
                    NodeMap* m = new NodeMap(Vector2(11, 11), Vector2(0, 0));
                    m->Decode(value);
                    maps.push_back(m);
                }
            }
        }

        if (readedJson[3].isMember("currentMap")) {
            currentMap->Decode(readedJson["currentMap"]);
        }

        jsonReadFile.close();
    }
}

void GameManager::PrintNewMap() {
    system("cls");
    currentMap->Draw();
    player->Draw();
    for (Object* object : objects) {
        object->Draw();
    }
    for (Chest* c : chests) {
        c->Draw();
    }
    for (Enemy* e : enemies) {
        e->Draw();
    }
    Print();
}

void GameManager::Print() {

    CC::Lock();
    CC::SetPosition(currentMap->GetSize().x + 10, 0);
    std::cout << "Monedas: " << player->GetCoins();
    CC::SetPosition(currentMap->GetSize().x + 10, 1);
    std::cout << "Vidas: " << player->GetLifes();
    CC::SetPosition(currentMap->GetSize().x + 10, 2);
    std::cout << "Pociones: " << player->GetAmountPotions();
    CC::SetPosition(currentMap->GetSize().x + 10, 3);
    /*std::cout << "Pociones: " << player->GetWeapon();*/ //Falta hacer un enum per poder fer el cout
    CC::Unlock();
    CC::Lock();
    CC::SetPosition(currentMap->GetSize().x, currentMap->GetSize().y);
    CC::Unlock();
}
void GameManager::Start() {
    player->ActivatePlayer(currentMap, &currentMapNumber, maps);
    Print();
}

void GameManager::Update() {
    for (Enemy* e : enemies) {
        Timer::DelayExecute(2000, [this, e]() {
            e->Move(currentMap);
        });
    }
;
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
    for (Object* o : objects)
        delete o;
    for (Chest* c : chests)
        delete c;
}