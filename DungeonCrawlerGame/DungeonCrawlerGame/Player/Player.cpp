#include "Player.h"
#include "../InputManager/InputManager.h"
#include "../InputManager/InputsConsts.h"

Player::Player() {
	position = new Node(Vector2(3,3));
	coinCounter = 0;
	lifes = 0;
	potionsCounter = 0;
	//Initialize weapons and equiped weapon
	InputSystem::KeyBinding* kb1 = IS.AddListener(K_UP, [this]() {
		position->SetPosition(position->GetPosition() + Vector2(0, 1));
		});

	InputSystem::KeyBinding* kb2 = IS.AddListener(K_LEFT, [this]() {
		position->SetPosition(position->GetPosition() + Vector2(-1, 0));
		});

	InputSystem::KeyBinding* kb3 = IS.AddListener(K_DOWN, [this]() {
		position->SetPosition(position->GetPosition() + Vector2(0, -1));
		});

	InputSystem::KeyBinding* kb4 = IS.AddListener(K_RIGHT, [this]() {
		position->SetPosition(position->GetPosition() + Vector2(1, 0));
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

void Player::Update(float dt) {
	
}

void Player::ReceiveDamage(int damage) {
	lifes -= damage;
}