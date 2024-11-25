#include "Enemy.h"
#include <thread>

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
		//std::thread* move = new std::thread(Move);
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

Object* Enemy::DropObject()
{
	int randomObject = rand() % 1;
	switch (randomObject) {
	case 0: objectType = ObjectType::POTION;
		object = new Object(objectType, object->GetNode());
		return object;
		break;
	case 1: objectType = ObjectType::COIN;
		object = new Object(objectType, object->GetNode());
		return object;
		break;
	}
}
