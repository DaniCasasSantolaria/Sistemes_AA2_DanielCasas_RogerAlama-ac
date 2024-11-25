#include "Player.h"
#include "../InputManager/InputsConsts.h"
#include "Weapons/Sword.h"


Player::Player() {
	position = new Node(Vector2(3, 3), new INodeContent(NodeContent::PLAYER));
	coinCounter = 0;
	lifes = 0;
	potionsCounter = 0;
	//Initialize weapons and equiped weapon
	equipedWeapon = new Sword();
	weapons.push_back(equipedWeapon);
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
	Json::Value jsonPlayer = Json::Value();
	jsonPlayer["position"] = position->Code();
	coinsMutex.lock();
	jsonPlayer["coins"] = coinCounter;
	coinsMutex.unlock();
	lifeMutex.lock();
	jsonPlayer["lifes"] = lifes;
	lifeMutex.unlock();
	jsonPlayer["maxlife"] = maxLife;
	jsonPlayer["potionsCounter"] = potionsCounter;
	jsonPlayer["cooldown"] = cooldown;
	jsonPlayer["lastTimeMoved"] = lastTimeMoved;
	Json::Value weaponsArray(Json::arrayValue);
	for(Weapon* weapon : weapons)
		weaponsArray.append(weapon->Code());
	jsonPlayer["weapons"] = weaponsArray;
	jsonPlayer["equipedWeapon"] = equipedWeapon->Code();
	json["player"] = jsonPlayer;
	return json;
}

void Player::Decode(Json::Value json) {
	if (position) {
		position->Decode(json);
	}

	coinsMutex.lock();
	if (json.isMember("coins")) {
		coinCounter = json["coins"].asUInt();
	}
	coinsMutex.unlock();

	lifeMutex.lock();
	if (json.isMember("lifes")) {
		lifes = json["lifes"].asUInt();
	}
	lifeMutex.unlock();

	if (json.isMember("maxlife")) {
		maxLife = json["maxlife"].asUInt();
	}

	if (json.isMember("potionsCounter")) {
		potionsCounter = json["potionsCounter"].asUInt();
	}

	if (json.isMember("cooldown")) {
		cooldown = json["cooldown"].asFloat();
	}

	if (json.isMember("lastTimeMoved")) {
		lastTimeMoved = json["lastTimeMoved"].asFloat();
	}

	if (json.isMember("weapons") && json["weapons"].isArray()) {
		for (const Json::Value& value : json["weapons"]) {
			Weapon* w = new Sword();
			w->Decode(json);
			weapons.push_back(w);
		}
	}
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
