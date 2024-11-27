#pragma once
#include "../Nodes/Node.h"

enum class ObjectType {COIN, POTION};

class Object {
private:
	ObjectType type;
	Node* node;

public:
	Object(ObjectType type, Node* node) : type(type), node(node) {}
	inline ObjectType GetType() { return type; }
	inline Node* GetNode() { return node; }
	void Draw();
	void SetNode(Node* node);
	inline ~Object() {
		delete node;
	}
};