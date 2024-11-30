#pragma once
#include "PlayerAttack.h"
#include "PlayerHealing.h"
#include "../Vector2/Vector2.h"
#include <vector>
#include "Weapons/Weapon.h"
#include <mutex>
#include "../Nodes/Node.h"
#include "../InputManager/InputManager.h"
#include "../Objects/Object.h"
#include "../Nodes/NodeMap.h"
#include "../Enemies/Enemy.h"

class Player : public PlayerAttackable, public PlayerDamageable, public PlayerHealing, public ICodable {
public:
	enum class PlayerState { RIGHT, LEFT, UP, DOWN, IDLE };
private:
	bool canMove = true;
	std::mutex classMutex;
	PlayerState movementState = PlayerState::IDLE;
	Node* position;
	std::mutex positionMutex;
	int coinCounter = 0;
	std::mutex coinsMutex;
	int lifes;
	std::mutex lifeMutex;
	int maxLife = 100;
	int potionsCounter;
	std::mutex potionsMutex;
	float cooldown = 1.0f;
	std::vector<Weapon*> weapons;
	Weapon* equipedWeapon;

public:
	Player(NodeMap* currentMap);
	~Player();
	void EnableMovementAfterDelay();
	Json::Value Code() override;
	void Decode(Json::Value json) override;
	void Attack(EnemyDamageable* enemy) override;
	void Move(NodeMap* currentMap, int* numMap, std::vector<NodeMap*>maps, std::vector<Enemy*> enemies);
	void ActivatePlayer(NodeMap* currentMap, int* numMap, std::vector<NodeMap*> maps, std::vector<Enemy*> enemies);
	inline void DesactivatePlayer() {IS.StopListen();}
	void ReceiveMoreCoins(int amount);
	int GetLifes();
	int GetCoins();
	int GetAmountPotions();
	inline void RecievePotion() { potionsCounter++; }
	inline float GetCooldownMovement() const { return cooldown; }
	inline PlayerState GetPlayerState() const { return movementState; }
	inline void SetMovementState(PlayerState m) { movementState = m; }
	Vector2 GetPosition();
	void UpdatePosition(NodeMap* currentMap, int* numMap, std::vector<NodeMap*> maps, std::vector<Enemy*> enemies);
	void ReceiveDamage(int damage) override;
	void TakeCoin();
	void TakePotion();
	void Heal(int lifeToHeal) override;
	int CheckPortals();
	void Draw();
	inline Weapon* GetWeapon() const {return equipedWeapon;} 
};