#include "Player.h"
#include "../InputManager/InputsConsts.h"
#include "Weapons/Sword.h"
#include "../ConsoleControl/ConsoleControl.h"


Player::Player() {
	position = new Node(Vector2(3, 3), new INodeContent(NodeContent::PLAYER));
	coinCounter = 0;
	lifes = 0;
	potionsCounter = 0;
	equipedWeapon = new Sword();
	weapons.push_back(equipedWeapon);
	InputSystem::KeyBinding* kb1 = IS.AddListener(K_UP, [this]() {
		std::cout << "GOLA";
		SetMovementState(PlayerState::UP);
		});

	InputSystem::KeyBinding* kb2 = IS.AddListener(K_LEFT, [this]() {
		SetMovementState(PlayerState::LEFT);
		});

	InputSystem::KeyBinding* kb3 = IS.AddListener(K_DOWN, [this]() {
		SetMovementState(PlayerState::DOWN);
		});

	InputSystem::KeyBinding* kb4 = IS.AddListener(K_RIGHT, [this]() {
		SetMovementState(PlayerState::RIGHT);
		});
	InputSystem::KeyBinding* kb5 = IS.AddListener(K_1, [this]() {
		Heal(15);
		});
	InputSystem::KeyBinding* kb6 = IS.AddListener(K_SPACE, [this]() {
		SetMovementState(PlayerState::ATTACK);
		});
}

Player::~Player() {
	for (Weapon* weapon : weapons)
		delete weapon;

	delete equipedWeapon;
	delete position;
}

void Player::Attack(EnemyDamageable* enemy) {
	enemy->ReceiveDamage(equipedWeapon->Attack());
}

void Player::ReceiveMoreCoins(int amount) {
	coinsMutex.lock();
	coinCounter += amount;
	coinsMutex.unlock();
}

Vector2 Player::GetPosition() {
	positionMutex.lock();
	Vector2 auxPos = position->GetPosition();
	positionMutex.unlock();
	return auxPos;
}

void Player::UpdatePosition() {
	positionMutex.lock();
	Vector2 previousPosition = position->GetPosition();
	positionMutex.unlock();
	Vector2 nextPosition{ 0, 0 };
	switch (movementState) {
	case PlayerState::RIGHT:
		nextPosition += Vector2(1, 0);
		break;
	case PlayerState::LEFT:
		nextPosition += Vector2(-1, 0);
		break;
	case PlayerState::UP:
		nextPosition += Vector2(0, 1);
		break;
	case PlayerState::DOWN:
		nextPosition += Vector2(0, -1);
		break;
	default:
		break;
	}
	positionMutex.lock();
	position->SetPosition(position->GetPosition() + nextPosition);
	positionMutex.unlock();
	movementState = PlayerState::IDLE;
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

void Player::Draw() {
	CC::Lock();
	CC::SetPosition(position->GetPosition().x, position->GetPosition().y);
	position->GetContent()->Draw();
	CC::Unlock();
}
