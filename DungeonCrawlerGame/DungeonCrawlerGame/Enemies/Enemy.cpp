#include "Enemy.h"
#include <thread>
#include "../ConsoleControl/ConsoleControl.h"

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

void Enemy::Update(float dt) {
	if(lastTimeMove < dt - movementCooldown) {
		lastTimeMove = dt;
	}
}

void Enemy::Draw() {
	CC::Lock();
	CC::SetPosition(node->GetPosition().x, node->GetPosition().y);
	node->GetContent()->Draw();
	CC::Unlock();
}

Object* Enemy::DropObject()
{
	return object;
}
