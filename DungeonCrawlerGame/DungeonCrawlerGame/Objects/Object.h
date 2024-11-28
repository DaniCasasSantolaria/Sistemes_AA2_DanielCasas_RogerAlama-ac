#pragma once
#include "../Nodes/Node.h"


class Object {
private:
	Node* node;

public:
	Object(Node* node) : node(node) {}
	inline void SetNodeContent(NodeContent content) { node->SetContent(content); }
	inline Node* GetNode() { return node; }
	void Draw();
	void SetNode(Node* node);
	inline ~Object() {
		delete node;
	}
};