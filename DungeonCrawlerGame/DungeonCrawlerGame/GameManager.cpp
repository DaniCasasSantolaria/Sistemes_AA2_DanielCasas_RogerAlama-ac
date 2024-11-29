#include "GameManager.h"
#include "../InputManager/InputManager.h"
#include "Timer/Timer.h"
#include "ConsoleControl/ConsoleControl.h"
#include "Enemies/SpawnerEnemies.h"
#include "Objects/SpawnerChests.h"
#include "Objects/SpawnerObjects.h"
#include <fstream>
#include <iostream>
//Clase mapamundi que tingui mapes, vector enemies i objects, funcio printmap (nodemap) que pasan-li el currentmap ho imprimeixi
// Vector de mapas en clase world en comptes de game manager
GameManager::GameManager() {
   /* srand(time(NULL));
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
    }*/
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
            player->Decode(readedJson[0]["player"]);
        }

        if (readedJson[1].isMember("enemies")) {
            for (Json::Value value : readedJson[1]["enemies"]) {
                Enemy* e = new Enemy(0, 0, Vector2(0,0), nullptr);
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
    player->Draw();
    for (Object* object : worldMap->GetObjects()) {
        object->Draw();
    }
    for (Chest* c : worldMap->GetChests()) {
        c->Draw();
    }
    for (Enemy* e : worldMap->GetEnemies()) {
        e->Draw();
    }
    Print();
}

void GameManager::Print() {

    CC::Lock();
    CC::SetPosition(worldMap->GetCurrentMap()->GetSize().x + 10, 0);
    std::cout << "Monedas: " << player->GetCoins();
    CC::SetPosition(worldMap->GetCurrentMap()->GetSize().x + 10, 1);
    std::cout << "Vidas: " << player->GetLifes();
    CC::SetPosition(worldMap->GetCurrentMap()->GetSize().x + 10, 2);
    std::cout << "Pociones: " << player->GetAmountPotions();
    CC::SetPosition(worldMap->GetCurrentMap()->GetSize().x + 10, 3);
    /*std::cout << "Pociones: " << player->GetWeapon();*/ //Falta hacer un enum per poder fer el cout
    CC::Unlock();
    CC::Lock();
    CC::SetPosition(0, worldMap->GetCurrentMap()->GetSize().y);
    CC::Unlock();
}
void GameManager::Start() {
    player->ActivatePlayer(worldMap->GetCurrentMap(), &currentMapNumber, worldMap->GetMaps());
    Print();
}

void GameManager::Update() {
    for (Enemy* e : worldMap->GetEnemies()) {
        Timer::DelayExecute(1000, [this, e]() {
            e->Move(worldMap->GetCurrentMap());
        });
    }
;
}

void GameManager::End() {
    player->DesactivatePlayer();
}

GameManager::~GameManager() {
    delete player;
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