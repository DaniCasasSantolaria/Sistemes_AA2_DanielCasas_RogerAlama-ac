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

Object* Enemy::DropObject()
{
	return object;
}
