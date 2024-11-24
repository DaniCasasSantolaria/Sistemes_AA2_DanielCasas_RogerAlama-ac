#include "Enemy.h"
#include <thread>

Json::Value Enemy::Code() {
	Json::Value json = Json::Value();
	json["life"] = life;
	json["attack"] = attack;
	json["movementCooldown"] = movementCooldown;
	json["lastTimeMove"] = lastTimeMove;
	json["isDead"] = isDead;
	return json;
}

void Enemy::Decode(Json::Value json) {
	life = json["life"].asInt();
	attack = json["attack"].asUInt();
	movementCooldown = json["movementCooldown"].asFloat();
	lastTimeMove = json["lastTimeMove"].asFloat();
	isDead = json["isDead"].asBool();
}

void Enemy::Move() {
	bool canMove = false;
	while(!canMove){
		int randomX = rand() % ((1 - (-1) + 1) - 1);
		int randomY = rand() % ((1 - (-1) + 1) - 1);
	}
}

void Enemy::Update(float dt) {
	if(lastTimeMove < dt - movementCooldown) {
		lastTimeMove = dt;
		std::thread move(&Enemy::Move, this);
		move.detach();
	}
}

void Enemy::Attack(PlayerDamageable* player) {
	player->ReceiveDamage(attack);
}

void Enemy::ReceiveDamage(int damage) {
	life -= damage;
	CheckLife();
}

void Enemy::CheckLife()
{
	if (life < 0) {
		isDead = true;
	}
}

void Enemy::LeaveObject()
{
	int randomObject = rand() % 2;
	switch (randomObject) {
	case 0: //potions
		break;
	case 1: //weapons
		break;
	case 2: //coins
		break;
	}
}
