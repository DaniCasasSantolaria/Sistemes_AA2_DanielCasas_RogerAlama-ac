#pragma once
#include "../Vector2/Vector2.h"

enum class NodeContent { WALL, ENEMY, OBJECT, NOTHING, PLAYER, INVALID};

class INodeContent {
private:
	char _content;
public:
	INodeContent(NodeContent content);
	void SetContent(NodeContent content);
	void Draw(Vector2 offset);
};