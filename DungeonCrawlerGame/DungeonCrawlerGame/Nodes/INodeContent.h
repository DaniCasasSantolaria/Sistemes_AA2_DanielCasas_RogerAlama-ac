#pragma once
#include "../Vector2/Vector2.h"
#include <mutex>

enum class NodeContent { WALL, ENEMY, OBJECT, NOTHING, PLAYER, PORTAL, INVALID};

class INodeContent {
private:
	char _content;
	std::mutex contentMutex;
public:
	INodeContent(NodeContent content);
	void SetContent(NodeContent content);
	void Draw(Vector2 offset);
};