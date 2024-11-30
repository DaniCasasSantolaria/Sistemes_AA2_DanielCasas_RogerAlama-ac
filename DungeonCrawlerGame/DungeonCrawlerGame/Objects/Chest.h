#pragma once
#include "Object.h"
#include "../Player/Player.h"
class Chest {
private:
	int map;
	Object* object;
	Node* node;
	int life = 2;
	
public:
	Chest(Object* object, Node* node, int currentMap)
		: object(object), node(node), map(currentMap) {}
	void DestroyChest(Player* player);
	inline void SetObject(Object* object) { this->object = object; }
	inline Object* GetObject() { return object; }
	inline int GetMap() { return map; }
	inline void ReceiveDamage() { life -= 1; };
	inline void SetPosition(Vector2 position) { this->node->SetPosition(position); }
	void Draw();
	inline Node* GetNode() { 
		return node; 
	}
	void SetNode(Node* node);
	inline ~Chest() {
		delete object;
		delete node;
	}
};