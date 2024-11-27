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
	inline void SetObject(Object* object) { this->object = object; }
	inline void ReceiveDamage() { life -= 1; };
	inline void SetPosition(Vector2 position) { this->node->SetPosition(position); }
	void Draw();
	void SetNode(Node* node);
	inline ~Chest() {
		delete object;
		delete node;
	}
};