#pragma once
#include "../Nodes/Node.h"


class Object {
private:
	int map;
	Node* node;

public:
	Object(Node* node, int currentMap) : node(node), map(currentMap){}
	inline void SetNodeContent(NodeContent content) { node->SetContent(content); }
	inline Node* GetNode() { return node; }
	inline int GetMap() { return map; }
	void Draw();
	void SetNode(Node* node);
	inline ~Object() {
		delete node;
	}
};