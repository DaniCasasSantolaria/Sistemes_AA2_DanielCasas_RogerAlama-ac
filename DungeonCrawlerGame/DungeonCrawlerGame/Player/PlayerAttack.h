#pragma once
#include "PlayerDamage.h"
#include "../Enemies/EnemyDamage.h"

class PlayerAttackable {
public:
	virtual void Attack(EnemyDamageable* enemy) = 0;
};