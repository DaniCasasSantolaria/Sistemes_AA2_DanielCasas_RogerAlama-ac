#pragma once
#include "PlayerAttack.h"
#include "../Vector2/Vector2.h"
#include <vector>
#include "Weapons/Weapon.h"
#include "../Nodes/Node.h"

class Player : public PlayerAttackable, public PlayerDamageable {
private:
	Node* position;
	int coinCounter;
	int lifes;
	int potionsCounter;
	std::vector<Weapon*> weapons;
	Weapon* equipedWeapon;
public:
	Player();
	~Player();
	void Attack(EnemyDamageable* enemy) override;
	void Update(float dt);
	void ReceiveDamage(int damage) override;
};