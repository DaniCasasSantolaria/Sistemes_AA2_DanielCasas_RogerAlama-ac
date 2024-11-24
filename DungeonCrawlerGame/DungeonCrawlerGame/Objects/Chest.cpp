#include "Chest.h"

void Chest::OpenChest(Player* player) {
	if (object->GetType() == ObjectType::POTION)
		player->RecievePotion();
	else if (object->GetType() == ObjectType::COIN)
		player->ReceiveMoreCoins(rand() % ((15 - 7 + 1) + 7));
}