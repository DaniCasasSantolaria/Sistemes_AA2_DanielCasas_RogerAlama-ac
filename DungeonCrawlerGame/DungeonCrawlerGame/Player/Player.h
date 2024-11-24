#pragma once
#include "PlayerAttack.h"
#include "PlayerHealing.h"
#include "../Vector2/Vector2.h"
#include <vector>
#include "Weapons/Weapon.h"
#include <mutex>
#include "../Nodes/Node.h"
#include "../InputManager/InputManager.h"
#include "../ICodable/ICodable.h"

class Player : public PlayerAttackable, public PlayerDamageable, public PlayerHealing, public ICodable {
private:
	Node* position;
	std::mutex positionMutex;
	int coinCounter = 0;
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
	Json::Value Code() override;
	void Decode(Json::Value json) override;
	void Attack(EnemyDamageable* enemy) override;
	inline void ActivatePlayer() {IS.StartListen();}
	inline void DesactivatePlayer() {IS.StopListen();}
	void ReceiveMoreCoins(int amount);
	inline void RecievePotion() { potionsCounter++; }
	void Move(int key, float dt);
	void Update(float dt);
	void ReceiveDamage(int damage) override;
	void Heal(int lifeToHeal) override;
};