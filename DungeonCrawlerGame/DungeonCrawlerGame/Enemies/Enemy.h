#pragma once
#include "EnemyAttack.h"
#include "../Objects/Object.h"
#include "../Nodes/Node.h"
#include "../Nodes/NodeMap.h"
#include <mutex>
#include "../Objects/SpawnerObjects.h"
class Enemy : public EnemyAttackable, public EnemyDamageable, public ICodable {
private:
	int life;
	int attack;
	float movementCooldown = 2.0f;
	float lastTimeMove = 0.0f;
	bool isDead = false;
	Node* node;
	Object* object;
	std::mutex positionMutex;
public:
	Enemy(int hp, int attck, Vector2 pos, NodeMap* currentMap)
		:
		life(hp), attack(attck) {
		node = new Node(pos, new INodeContent(NodeContent::ENEMY));
		int random = rand() % 2;
		NodeContent content;
		if (random == 0)
			content = NodeContent::POTION;
		else
			content = NodeContent::COIN;
		INodeContent* nodeContent;
		object = new Object(new Node(pos, new INodeContent(content)));
		currentMap->SafePickNode(pos, [this](Node* auxNode) {
			auxNode->SetContent(NodeContent::ENEMY);
			});
	}
	void Move(NodeMap* currentMap);
	Json::Value Code() override;
	void Decode(Json::Value json) override;
	void Update();
	inline void Attack(PlayerDamageable* player) override { player->ReceiveDamage(attack); }
	inline void ReceiveDamage(int damage) override { life -= damage; }
	void Draw();
	Object* DropObject();
	inline bool IsDead() { return life <= 0; }
	inline void SetPosition(Vector2 position) { node->SetPosition(position); }
	inline ~Enemy() {
		delete node;
		delete object;
	}
	inline Vector2 GetPosition() {
		positionMutex.lock();
		Vector2 pos = node->GetPosition();
		positionMutex.unlock();
		return pos;
	}
};
