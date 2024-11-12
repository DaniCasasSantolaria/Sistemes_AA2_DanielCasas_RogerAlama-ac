#pragma once
#include "EnemyAttack.h"

class Enemy : public EnemyAttackable, public EnemyDamageable {
private:
	int life;
	int attack;
public:
	Enemy() = default;
	Enemy(int hp, int attck)
		: life(hp), attack(attck) {}
	void Attack(PlayerDamageable* player) override;
	void ReceiveDamage(int damage) override;
};