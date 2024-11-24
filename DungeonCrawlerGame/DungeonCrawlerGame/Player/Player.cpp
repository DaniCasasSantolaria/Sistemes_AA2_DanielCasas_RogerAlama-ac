#include "Player.h"
#include "../InputManager/InputsConsts.h"


Player::Player() {
	position = new Node(Vector2(3, 3), new INodeContent(NodeContent::PLAYER));
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

Json::Value Player::Code() {
	Json::Value json = Json::Value();
	json.append(position->Code());
	coinsMutex.lock();
	json["coins"] = coinCounter;
	coinsMutex.unlock();
	lifeMutex.lock();
	json["lifes"] = lifes;
	lifeMutex.unlock();
	json["maxlife"] = maxLife;
	json["potionsCounter"] = potionsCounter;
	json["cooldown"] = cooldown;
	json["lastTimeMoved"] = lastTimeMoved;
	for(Weapon* weapon : weapons)
		json.append(weapon->Code());
	json.append(equipedWeapon->Code());
	return json;
}

void Player::Decode(Json::Value json) {
	position->Decode(json);
	coinsMutex.lock();
	coinCounter = json["coins"].asUInt();
	coinsMutex.unlock();
	lifeMutex.lock();
	lifes = json["lifes"].asUInt();
	lifeMutex.unlock();
	maxLife = json["maxlife"].asUInt();
	potionsCounter = json["potionsCounter"].asUInt();
	cooldown = json["cooldown"].asFloat();
	lastTimeMoved = json["lastTimeMoved"].asFloat();
	/*for (Json::Value value : readedJson) {
		Weapon* w = ICodable::FromJson<Weapon>(value);
		readWeapons.push_back(w);
	}*/
}

void Player::Attack(EnemyDamageable* enemy) {
	equipedWeapon->Attack();
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

void Player::ReceiveMoreCoins(int amount) {
	coinsMutex.lock();
	coinCounter += amount;
	coinsMutex.unlock();
}

void Player::Update(float dt) {
	if (lastTimeMoved < dt - cooldown) {
		lastTimeMoved = dt;
		std::thread movement(&Player::ActivatePlayer, this);
		movement.detach();
	}
}

void Player::ReceiveDamage(int damage) {
	lifeMutex.lock();
	lifes -= damage;
	lifeMutex.unlock();
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
