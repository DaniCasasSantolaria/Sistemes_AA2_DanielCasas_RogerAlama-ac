#pragma once
#include "EnemyAttack.h"
#include "../Objects/Object.h"
class Enemy : public EnemyAttackable, public EnemyDamageable {
private:
	int life;
	int attack;
	float movementCooldown = 2.0f;
	float lastTimeMove = 0.0f;
	Object* object;
public:

	Enemy() = default;
	Enemy(int hp, int attck)
		: life(hp), attack(attck) {}
	void Move();
	void Update(float dt);
	inline void Attack(PlayerDamageable* player) override { player->ReceiveDamage(attack); }
	inline void ReceiveDamage(int damage) override { life -= damage; }
	Object* DropObject();
	inline bool IsDead() { return life <= 0; }

};