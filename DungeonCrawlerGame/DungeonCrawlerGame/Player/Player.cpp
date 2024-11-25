#include "Player.h"
#include "../InputManager/InputsConsts.h"
#include "Weapons/Sword.h"


Player::Player() {
	position = new Node(Vector2(3, 3), new INodeContent(NodeContent::PLAYER));
	coinCounter = 0;
	lifes = 0;
	potionsCounter = 0;
	equipedWeapon = new Sword();
	weapons.push_back(equipedWeapon);
	InputSystem::KeyBinding* kb1 = IS.AddListener(K_UP, [this]() {
		movementState = Movement::UP;
		});

	InputSystem::KeyBinding* kb2 = IS.AddListener(K_LEFT, [this]() {
		movementState = Movement::LEFT;
		});

	InputSystem::KeyBinding* kb3 = IS.AddListener(K_DOWN, [this]() {
		movementState = Movement::DOWN;
		});

	InputSystem::KeyBinding* kb4 = IS.AddListener(K_RIGHT, [this]() {
		movementState = Movement::RIGHT;
		});
	InputSystem::KeyBinding* kb5 = IS.AddListener(K_1, [this]() {
		Heal(15);
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

void Player::Move(NodeMap* map) {
	/*if (lastTimeMoved < dt - cooldown) {
		lastTimeMoved = dt;
		switch (key) {
		case K_RIGHT:
			break;
		case K_LEFT:
			break;
		case K_UP:
			break;
		case K_DOWN:
			break;
		}
	}*/
	positionMutex.lock();
	Vector2 previousPosition = position->GetPosition();
	positionMutex.unlock();
	Vector2 nextPosition {0, 0};
	switch (movementState) {
	case Movement::RIGHT:
		nextPosition += Vector2(1, 0);
		break;
	case Movement::LEFT:
		nextPosition += Vector2(-1, 0);
		break;
	case Movement::UP:
		nextPosition += Vector2(0, 1);
		break;
	case Movement::DOWN:
		nextPosition += Vector2(0, -1);
		break;
	default:
		break;
	}
	if (map->GetNodeContent(nextPosition)->GetContent() == NodeContent::NOTHING) {
		positionMutex.lock();
		position->SetPosition(position->GetPosition() + nextPosition);
		positionMutex.unlock();
	}
}

void Player::ReceiveMoreCoins(int amount) {
	coinsMutex.lock();
	coinCounter += amount;
	coinsMutex.unlock();
}

void Player::Update(float dt) {
	if (lastTimeMoved < dt - cooldown) {
		lastTimeMoved = dt;
	}
}

void Player::ReceiveDamage(int damage) {
	lifeMutex.lock();
	lifes -= damage;
	lifeMutex.unlock();
}

void Player::TakeObject(Object* object) {
	if (object->GetType() == ObjectType::COIN) {
		coinsMutex.lock();
		coinCounter += rand() % ((5 - 3 + 1) + 3);
		coinsMutex.unlock();
	}
	else if (object->GetType() == ObjectType::POTION) {
		potionsCounter++;
	}
}

void Player::Heal(int lifeToHeal)
{
	if (potionsCounter < 0)
		return;
	if (lifes < maxLife) {
		lifeMutex.lock();
		lifes += lifeToHeal;
		if (lifes > maxLife) {
			lifes = maxLife;
		}
		lifeMutex.unlock();
		potionsCounter--;
	}
}
