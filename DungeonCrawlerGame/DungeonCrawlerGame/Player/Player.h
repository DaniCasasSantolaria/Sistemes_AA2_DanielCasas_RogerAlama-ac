#pragma once
#include "PlayerAttack.h"
#include "PlayerHealing.h"
#include "../Vector2/Vector2.h"
#include <vector>
#include "Weapons/Weapon.h"
#include <mutex>
#include "../Nodes/Node.h"
#include "../InputManager/InputManager.h"


class Player : public PlayerAttackable, public PlayerDamageable, public PlayerHealing {
private:
	Node* position;
	std::mutex positionMutex;
	int coinCounter;
	std::mutex coinsMutex;
	int lifes;
	std::mutex lifeMutex;
	int maxLife = 100;
	int potionsCounter;
	float cooldown = 1.0f;
	float lastTimeMoved = 0.0f;
	std::vector<Weapon*> weapons;
	Weapon* equipedWeapon;

public:
	Player();
	~Player();
	void Attack(EnemyDamageable* enemy) override;
	inline void ActivatePlayer(){IS.StartListen();}
	inline void DesactivatePlayer() {IS.StopListen();}
	void Update(float dt);
	void ReceiveDamage(int damage) override;
	void Heal(int lifeToHeal) override;
};