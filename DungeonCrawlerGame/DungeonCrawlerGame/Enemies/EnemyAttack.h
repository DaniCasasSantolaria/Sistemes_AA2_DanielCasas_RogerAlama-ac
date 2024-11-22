#pragma once
#include "EnemyDamage.h"
#include "../Player/PlayerDamage.h"

class EnemyAttackable {
public:
	virtual void Attack(PlayerDamageable* player) = 0;
};