#pragma once
#include "EnemyAttack.h"

class Enemy : public EnemyAttackable, public EnemyDamageable {
private:
	int life;
	int attack;
	float movementCooldown = 2.0f;
	float lastTimeMove = 0.0f;
	bool isDead = false;
public:

	Enemy() = default;
	Enemy(int hp, int attck)
		: life(hp), attack(attck) {}
	void Move();
	void Update(float dt);
	void Attack(PlayerDamageable* player) override;
	void ReceiveDamage(int damage) override;
	void CheckLife();
	void LeaveObject();
	inline bool GetIfIsDead() { return isDead; }
	inline bool SetIfIsDead(bool checkDeath) { checkDeath = isDead; }
};