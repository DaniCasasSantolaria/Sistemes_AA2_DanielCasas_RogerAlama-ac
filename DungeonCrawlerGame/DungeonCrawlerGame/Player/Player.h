#pragma once
#include "PlayerAttack.h"
#include "../Vector2/Vector2.h"
#include <vector>
#include "Weapons/Weapon.h"

class Player : public PlayerAttackable, public PlayerDamageable {
private:
	Vector2 position;
	int coinCounter;
	int lifes;
	int potionsCounter;
	std::vector<Weapon*> weapons;
	Weapon* equipedWeapon;
public:
	Player() = default;
	~Player();
	void Attack(EnemyDamageable* enemy) override;
	void ReceiveDamage(int damage) override;
};