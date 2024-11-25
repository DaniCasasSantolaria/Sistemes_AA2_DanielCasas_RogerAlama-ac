#pragma once
#include "Object.h"
#include "../Player/Player.h"
class Chest {
private:
	Object* object;
	Node* node;
	int life = 2;
	
public:
	Chest(Object* object, Node* node)
		: object(object), node(node) {}
	void DestroyChest(Player* player);
	inline ~Chest() {
		delete object;
		delete node;
	}
	inline void ReceiveDamage() { life -= 1; };
};