#include "Player.h"
#include "../InputManager/InputsConsts.h"
#include "Weapons/Sword.h"
#include "../ConsoleControl/ConsoleControl.h"


Player::Player() {
	position = new Node(Vector2(3, 3), new INodeContent(NodeContent::PLAYER));
	coinCounter = 0;
	lifes = 100;
	potionsCounter = 0;
	equipedWeapon = new Sword();
	weapons.push_back(equipedWeapon);
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

	if (json.isMember("weapons") && json["weapons"].isArray()) {
		for (const Json::Value& value : json["weapons"]) {
			Weapon* w = new Sword();
			w->Decode(json);
			weapons.push_back(w);
		}
	}
}

void Player::Attack(EnemyDamageable* enemy) {
	enemy->ReceiveDamage(equipedWeapon->Attack());
}

void Player::ActivatePlayer(NodeMap* currentMap) {
	InputSystem::KeyBinding* kb1 = IS.AddListener(K_UP, [this, currentMap]() {
		SetMovementState(PlayerState::UP);
		UpdatePosition(currentMap);
		});

	InputSystem::KeyBinding* kb2 = IS.AddListener(K_LEFT, [this, currentMap]() {
		SetMovementState(PlayerState::LEFT);
		UpdatePosition(currentMap);
		});

	InputSystem::KeyBinding* kb3 = IS.AddListener(K_DOWN, [this, currentMap]() {
		SetMovementState(PlayerState::DOWN);
		UpdatePosition(currentMap);
		});

	InputSystem::KeyBinding* kb4 = IS.AddListener(K_RIGHT, [this, currentMap]() {
		SetMovementState(PlayerState::RIGHT);
		UpdatePosition(currentMap);
		});
	InputSystem::KeyBinding* kb5 = IS.AddListener(K_1, [this, currentMap]() {
		Heal(15);
		});
	InputSystem::KeyBinding* kb6 = IS.AddListener(K_SPACE, [this, currentMap]() {
		/*SetMovementState(PlayerState::ATTACK);*/
		});
	IS.StartListen();
}

void Player::ReceiveMoreCoins(int amount) {
	coinsMutex.lock();
	coinCounter += amount;
	coinsMutex.unlock();
}

int Player::GetLifes() {
	lifeMutex.lock();
	int amountLifes = lifes;
	lifeMutex.unlock();

	return amountLifes;
}

int Player::GetCoins() {
	coinsMutex.lock();
	int coins = coinCounter;
	coinsMutex.unlock();
	return coins;
}

int Player::GetAmountPotions() {
	potionsMutex.lock();
	int amountPotions = potionsCounter;
	potionsMutex.unlock();
	return amountPotions;
}

Vector2 Player::GetPosition() {
	positionMutex.lock();
	Vector2 auxPos = position->GetPosition();
	positionMutex.unlock();
	return auxPos;
}

void Player::UpdatePosition(NodeMap* currentMap) {
	positionMutex.lock();
	Vector2 previousPosition = position->GetPosition();
	positionMutex.unlock();
	Vector2 nextPosition = previousPosition;
	switch (movementState) {
	case PlayerState::RIGHT:
		nextPosition.x++;
		break;
	case PlayerState::LEFT:
		nextPosition.x--;
		break;
	case PlayerState::UP:
		nextPosition.y--;
		break;
	case PlayerState::DOWN:
		nextPosition.y++;
		break;
	default:
		break;
	}
	bool canMove = false;

	currentMap->SafePickNode(nextPosition, [this, nextPosition, &canMove](Node* auxNode) {
		if (auxNode->GetINodeContent()->GetContent() == NodeContent::NOTHING) {
			canMove = true;
			positionMutex.lock();
			position->SetPosition(nextPosition);
			positionMutex.unlock();
			auxNode->SetContent(NodeContent::PLAYER);
			CC::Lock();
			CC::SetPosition(position->GetPosition().x, position->GetPosition().y);
			auxNode->DrawContent();
			CC::Unlock();

		}

		else if (auxNode->GetINodeContent()->GetContent() == NodeContent::PORTAL) {
			positionMutex.lock();
			position->SetPosition(nextPosition);
			positionMutex.unlock();
		}
		});
	if (canMove) {
		currentMap->SafePickNode(previousPosition, [this, previousPosition](Node* auxNode) {
			if (auxNode->GetINodeContent()->GetContent() == NodeContent::PLAYER) {
				auxNode->SetContent(NodeContent::NOTHING);
				CC::Lock();
				CC::SetPosition(previousPosition.x, previousPosition.y);
				auxNode->DrawContent();
				CC::Unlock();
			}
			});
	}
	
	movementState = PlayerState::IDLE;
	CC::Lock();
	CC::SetPosition(0, currentMap->GetSize().y);
	CC::Unlock();
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
	potionsMutex.lock();
	int potions = potionsCounter;
	potionsMutex.unlock();

	if (potions < 0)
		return;

	if (lifes < maxLife) {
		lifeMutex.lock();
		lifes += lifeToHeal;
		if (lifes > maxLife) {
			lifes = maxLife;
		}
		lifeMutex.unlock();
		potionsMutex.lock();
		potionsCounter--;
		potionsMutex.unlock();
	}
}

void Player::Draw() {
	CC::Lock();
	CC::SetPosition(position->GetPosition().x, position->GetPosition().y);
	position->GetContent()->Draw();
	CC::Unlock();
}
