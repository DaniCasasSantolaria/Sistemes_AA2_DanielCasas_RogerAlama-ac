#include "Player.h"
#include "../InputManager/InputsConsts.h"
#include "Weapons/Sword.h"
#include "../ConsoleControl/ConsoleControl.h"

void Player::EnableMovementAfterDelay() {
	classMutex.lock();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	classMutex.unlock();
	canMove = true;
}

Player::Player(NodeMap* currentMap) {
	position = new Node(Vector2(currentMap->GetOffset().x + 5, currentMap->GetOffset().y + 5), new INodeContent(NodeContent::PLAYER));
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

void Player::Move(NodeMap* currentMap, int* numMap, std::vector<NodeMap*> maps, std::vector<Enemy*> enemies) {
	if (canMove) {
		canMove = false;
		UpdatePosition(currentMap, numMap, maps, enemies);
		std::thread(&Player::EnableMovementAfterDelay, this).detach();
	}
}

void Player::ActivatePlayer(NodeMap* currentMap, int* numMap, std::vector<NodeMap*> maps, std::vector<Enemy*> enemies) {
	InputSystem::KeyBinding* kb1 = IS.AddListener(K_UP, [this, currentMap, numMap, maps, enemies]() {
		SetMovementState(PlayerState::UP);
		Move(currentMap, numMap, maps, enemies);
		});

	InputSystem::KeyBinding* kb2 = IS.AddListener(K_LEFT, [this, currentMap, numMap, maps, enemies]() {
		SetMovementState(PlayerState::LEFT);
		Move(currentMap, numMap, maps, enemies);
		});

	InputSystem::KeyBinding* kb3 = IS.AddListener(K_DOWN, [this, currentMap, numMap, maps, enemies]() {
		SetMovementState(PlayerState::DOWN);
		Move(currentMap, numMap, maps, enemies);
		});

	InputSystem::KeyBinding* kb4 = IS.AddListener(K_RIGHT, [this, currentMap, numMap, maps, enemies]() {
		SetMovementState(PlayerState::RIGHT);
		Move(currentMap, numMap, maps, enemies);
		});
	InputSystem::KeyBinding* kb5 = IS.AddListener(K_1, [this]() {
		Heal(15);
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

void Player::UpdatePosition(NodeMap* currentMap, int* numMap, std::vector<NodeMap*> maps, std::vector<Enemy*> enemies) {
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
	NodeMap* nextMap = nullptr;
	Enemy* damagedEnemy = nullptr;
	currentMap->SafePickNode(nextPosition, [this, nextPosition, &canMove, &numMap, maps, enemies, &nextMap, &damagedEnemy](Node* auxNode) {
		if (auxNode->GetContent()->GetContent() == NodeContent::ENEMY) {
			for (Enemy* e : enemies) {
				if (e->GetPosition().x == auxNode->GetPosition().x && e->GetPosition().y == auxNode->GetPosition().y) {
					damagedEnemy = e;
					Attack(damagedEnemy);
					break;
				}
			}
		}
		else if (auxNode->GetINodeContent()->GetContent() == NodeContent::NOTHING) {
			canMove = true;
			positionMutex.lock();
			position->SetPosition(nextPosition);
			positionMutex.unlock();
			auxNode->SetContent(NodeContent::PLAYER);
			auxNode->DrawContent(nextPosition);

		}
		else if (auxNode->GetINodeContent()->GetContent() == NodeContent::COIN) {
			canMove = true;
			positionMutex.lock();
			position->SetPosition(nextPosition);
			positionMutex.unlock();
			auxNode->SetContent(NodeContent::PLAYER);
			auxNode->DrawContent(nextPosition);
			TakeCoin();
		}
		else if (auxNode->GetINodeContent()->GetContent() == NodeContent::POTION) {
			canMove = true;
			positionMutex.lock();
			position->SetPosition(nextPosition);
			positionMutex.unlock();
			auxNode->SetContent(NodeContent::PLAYER);
			auxNode->DrawContent(nextPosition);
			TakePotion();
		}
		else if (auxNode->GetINodeContent()->GetContent() == NodeContent::PORTAL) {
			int num = CheckPortals();
			*numMap += num;
			nextMap = maps[*numMap];
			canMove = true;
		}
	});
	if (canMove) {
		currentMap->SafePickNode(previousPosition, [this, previousPosition](Node* auxNode) {
			if (auxNode->GetINodeContent()->GetContent() == NodeContent::PLAYER) {
				auxNode->SetContent(NodeContent::NOTHING);
				auxNode->DrawContent(previousPosition);
			}
		});
	}
	if (damagedEnemy != nullptr) {
		if (damagedEnemy->IsDead()) {
			currentMap->SafePickNode(damagedEnemy->GetPosition(), [this, &damagedEnemy](Node* auxNode) {
				auxNode->SetContent(NodeContent::NOTHING);
				delete damagedEnemy;
				});
		}
	}
	if (nextMap != nullptr) {
		currentMap = nextMap;
		Vector2 newPosPlayer = Vector2(currentMap->GetOffset().x + currentMap->GetSize().x / 2, currentMap->GetOffset().y + currentMap->GetSize().y / 2);
		currentMap->SafePickNode(newPosPlayer, [this, newPosPlayer](Node* auxNode) {
			auxNode->SetContent(NodeContent::PLAYER);
			positionMutex.lock();
			position->SetPosition(newPosPlayer);
			positionMutex.unlock();
			});
		system("cls");
		currentMap->Draw();
		std::string weapon = "";
		switch (equipedWeapon->GetWeaponType()) {
		case WeaponType::SWORD:
			weapon = "espada";
			break;
		case WeaponType::SPEAR:
			weapon = "lanza";
			break;
		default:
			break;
		}
		CC::Lock();
		CC::SetPosition(currentMap->GetSize().x * 4, 0);
		std::cout << "Monedas: " << coinCounter;
		CC::SetPosition(currentMap->GetSize().x * 4, 1);
		std::cout << "Vidas: " << lifes;
		CC::SetPosition(currentMap->GetSize().x * 4, 2);
		std::cout << "Pociones: " << potionsCounter;
		CC::SetPosition(currentMap->GetSize().x * 4, 3);
		std::cout << "Arma: " << weapon;
		CC::Unlock();
		CC::Lock();
		CC::SetPosition(0, currentMap->GetSize().y);
		CC::Unlock();
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

void Player::TakeCoin() {
	coinsMutex.lock();
	coinCounter++;
	int coins = coinCounter;
	coinsMutex.unlock();
	CC::Lock();
	CC::SetPosition(33 + 11, 0);
	std::cout << "Monedas: " << coinCounter;
	CC::Unlock();
	CC::Lock();
	CC::SetPosition(33 + 11, 11);
	CC::Unlock();
}

void Player::TakePotion() {
	potionsMutex.lock();
	potionsCounter++;
	int potions = potionsCounter;
	potionsMutex.unlock();

	CC::Lock();
	CC::SetPosition(33 + 11, 2);
	std::cout << "Pociones: " << potions;
	CC::SetPosition(33 + 11, 11);
	CC::Unlock();
}

void Player::Heal(int lifeToHeal)
{
	potionsMutex.lock();
	int potions = potionsCounter;
	potionsMutex.unlock();

	if (potions < 0)
		return;
	lifeMutex.lock();
	int life = lifes;
	lifeMutex.unlock();
	if (life < maxLife) {
		lifeMutex.lock();
		lifes += lifeToHeal;
		life = lifes;
		if (lifes > maxLife) {
			lifes = maxLife;
			life = lifes;
			lifeMutex.unlock();
		}
		else {
			lifeMutex.unlock();
		}
		potionsMutex.lock();
		potionsCounter--;
		potions = potionsCounter;
		potionsMutex.unlock();
	}
	CC::Lock();
	CC::SetPosition(33 + 11, 2);
	std::cout << "Pociones: " << potions;
	CC::SetPosition(33 + 11, 1);
	std::cout << "Vidas: " << life;
	CC::SetPosition(33 + 11, 11);
	CC::Unlock();
}

int Player::CheckPortals() {
	positionMutex.lock();
	Vector2 pos = position->GetPosition();
	positionMutex.unlock();
	int nextMap = 0;
	switch (movementState) {
	case Player::PlayerState::DOWN:
		nextMap = 3;
		pos.y++;
		break;
	case Player::PlayerState::LEFT:
		nextMap = -1;
		pos.x--;
		break;
	case Player::PlayerState::RIGHT:
		nextMap = 1;
		pos.x++;
		break;
	case Player::PlayerState::UP:
		nextMap = -3;
		pos.y--;
		break;
	}
	return nextMap;
}

void Player::Draw() {
	position->Lock();
	position->GetContent()->Draw(position->GetPosition());
	position->Unlock();
}
