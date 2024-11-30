#include "Chest.h"
#include "../ConsoleControl/ConsoleControl.h"

void Chest::DestroyChest(Player* player) {
	if (object->GetNode()->GetContent()->GetContent() == NodeContent::POTION)
		player->RecievePotion();
	else if (object->GetNode()->GetContent()->GetContent() == NodeContent::COIN)
		player->ReceiveMoreCoins(rand() % ((15 - 7 + 1) + 7));
}

void Chest::Draw() {
	node->DrawContent(node->GetPosition());
}

void Chest::SetNode(Node* node) {;
	this->node = node;
}
