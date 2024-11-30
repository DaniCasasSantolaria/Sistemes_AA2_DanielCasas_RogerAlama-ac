#include "Enemy.h"
#include "../ConsoleControl/ConsoleControl.h"
#include <thread>
#include <ctime>
#include "../Timer/Timer.h"
Json::Value Enemy::Code() {
	Json::Value json = Json::Value();
	Json::Value jsonEnemy = Json::Value();
	jsonEnemy["life"] = life;
	jsonEnemy["attack"] = attack;
	jsonEnemy["movementCooldown"] = movementCooldown;
	jsonEnemy["lastTimeMove"] = lastTimeMove;
	jsonEnemy["isDead"] = isDead;
	json["enemy"] = jsonEnemy;
	return json;
}

void Enemy::Decode(Json::Value json) {
	life = json["life"].asInt();
	attack = json["attack"].asUInt();
	movementCooldown = json["movementCooldown"].asFloat();
	lastTimeMove = json["lastTimeMove"].asFloat();
	isDead = json["isDead"].asBool();
}

void Enemy::Move(NodeMap* currentMap, int currentMapNumber) {
	bool canMove = false;
	positionMutex.lock();
	Vector2 lastPos = node->GetPosition();
	positionMutex.unlock();
	int maxAttempts = 20;
	while (!canMove && maxAttempts > 0) {
		int randomX = (rand() % 3) - 1;
		int randomY = (rand() % 3) - 1;

		Vector2 pos{ randomX, randomY };
		Vector2 nextPos = Vector2(lastPos.x + pos.x, lastPos.y + pos.y);
	
		currentMap->SafePickNode(nextPos, [this, nextPos, &canMove, currentMapNumber](Node* auxNode) {
			if (auxNode->GetINodeContent()->GetContent() == NodeContent::NOTHING) {
				positionMutex.lock();
				node->SetPosition(nextPos);
				positionMutex.unlock();
				auxNode->SetContent(NodeContent::ENEMY);
				if(currentMapNumber == map)
					auxNode->DrawContent(nextPos);
				canMove = true;
			}
		});
		if (canMove) {
			currentMap->SafePickNode(lastPos, [this, lastPos, currentMapNumber](Node* auxNode) {
				if (auxNode->GetINodeContent()->GetContent() == NodeContent::ENEMY) {
					auxNode->SetContent(NodeContent::NOTHING);
					if (currentMapNumber == map)
						auxNode->DrawContent(lastPos);
				}
			});
		}
		maxAttempts--;
	;}
	CC::Lock();
	CC::SetPosition(0, currentMap->GetSize().y);
	CC::Unlock();
}

void Enemy::Draw() {
	node->DrawContent(node->GetPosition());
}

Object* Enemy::DropObject() {
	return object;
}