#include "Player.h"
#include "../InputManager/InputsConsts.h"


Player::Player() {
	position = new Node(Vector2(3,3));
	coinCounter = 0;
	lifes = 0;
	potionsCounter = 0;
	//Initialize weapons and equiped weapon
	InputSystem::KeyBinding* kb1 = IS.AddListener(K_UP, [this]() {
		positionMutex.lock();
		position->SetPosition(position->GetPosition() + Vector2(0, 1));
		positionMutex.unlock();
		});

	InputSystem::KeyBinding* kb2 = IS.AddListener(K_LEFT, [this]() {
		positionMutex.lock();
		position->SetPosition(position->GetPosition() + Vector2(-1, 0));
		positionMutex.unlock();
		});

	InputSystem::KeyBinding* kb3 = IS.AddListener(K_DOWN, [this]() {
		positionMutex.lock();
		position->SetPosition(position->GetPosition() + Vector2(0, -1));
		positionMutex.unlock();
		});

	InputSystem::KeyBinding* kb4 = IS.AddListener(K_RIGHT, [this]() {
		positionMutex.lock();
		position->SetPosition(position->GetPosition() + Vector2(1, 0));
		positionMutex.unlock();
		});
	InputSystem::KeyBinding* kb5 = IS.AddListener(K_E, [this]() {
		lifeMutex.lock();
		
		lifeMutex.unlock();
		});
}

Player::~Player() {
	for (Weapon* weapon : weapons)
		delete weapon;

	delete equipedWeapon;
	delete position;
}

void Player::Attack(EnemyDamageable* enemy) {
	equipedWeapon->Attack();
}

void Player::ActivatePlayer() {
	IS.StartListen();
}

//void Player::Move(int key, float dt)
//{
//	if (lastTimeMoved < dt - cooldown) {
//		lastTimeMoved = dt;
//		switch (key) {
//		case K_RIGHT:
//			break;
//		case K_LEFT:
//			break;
//		case K_UP:
//			break;
//		case K_DOWN:
//			break;
//		}
//	}
//}

void Player::Update(float dt) {
	
	std::thread* movement = new std::thread(ActivatePlayer);
	movement->detach();
}

void Player::ReceiveDamage(int damage) {
	lifeMutex.lock();
	lifes -= damage;
	lifeMutex.unlock();
}

void Player::Heal(int lifeToHeal)
{
	if (lifes < maxLife) {
		lifeMutex.lock();
		lifes += lifeToHeal;
		if (lifes > maxLife) {
			lifes = maxLife;
		}
		lifeMutex.unlock();
	}
	
}
