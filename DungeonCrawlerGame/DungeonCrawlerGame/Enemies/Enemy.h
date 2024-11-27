#pragma once
#include "EnemyAttack.h"
#include "../Objects/Object.h"
#include "../Nodes/Node.h"
#include "../Nodes/NodeMap.h"
#include <mutex>

class Enemy : public EnemyAttackable, public EnemyDamageable, public ICodable {
private:
	int life;
	int attack;
	float movementCooldown = 2.0f;
	float lastTimeMove = 0.0f;
	bool isDead = false;
	Node* node;
	Object* object;
	std::mutex _positionMutex;
public:
	Enemy(int hp, int attck, Vector2 pos)
		:
		 life(hp), attack(attck) {
		node = new Node(pos, new INodeContent(NodeContent::ENEMY));
	}
	void Move(NodeMap* currentMap);
	Json::Value Code() override;
	void Decode(Json::Value json) override;
	void Update();
	inline void Attack(PlayerDamageable* player) override { player->ReceiveDamage(attack); }
	inline void ReceiveDamage(int damage) override { life -= damage; }
	inline void SpawnEnemy(Vector2 position) { Node* node = new Node(position, new INodeContent(NodeContent::ENEMY)); }
	void Draw();
	Object* DropObject();
	inline bool IsDead() { return life <= 0; }
	inline void SetPosition(Vector2 position) { node->SetPosition(position); }
	inline ~Enemy() {
		delete node;
		delete object;
	}
};