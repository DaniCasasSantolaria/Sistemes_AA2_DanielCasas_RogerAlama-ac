#include "Enemy.h"
#include "../ConsoleControl/ConsoleControl.h"
#include <thread>

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

void Enemy::Move(NodeMap* currentMap) {
	bool canMove = false;
	while(!canMove){
		int randomX = rand() % ((1 - (-1) + 1) - 1);
		int randomY = rand() % ((1 - (-1) + 1) - 1);
		Vector2 pos{ randomX, randomY };
		currentMap->SafePickNode(pos, [this, pos](Node* auxNode) {
			if (auxNode->GetINodeContent()->GetContent() == NodeContent::NOTHING) {
				_positionMutex.lock();
				node->SetPosition(Vector2(pos.x, pos.y));
				_positionMutex.unlock();
				Draw();
			}
			});
	}

}

void Enemy::Update() {
	/*std::thread move(&Enemy::Move, this);
	move.detach();*/
}

void Enemy::Draw() {
	CC::Lock();
	CC::SetPosition(node->GetPosition().x, node->GetPosition().y);
	node->GetContent()->Draw();
	CC::Unlock();
}

Object* Enemy::DropObject() {
	return object;
}