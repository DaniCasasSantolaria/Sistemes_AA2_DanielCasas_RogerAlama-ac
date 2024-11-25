#pragma once
#include "../Vector2/Vector2.h"
#include <mutex>

enum class NodeContent { WALL, ENEMY, OBJECT, NOTHING, PLAYER, PORTAL, INVALID};

class INodeContent {
private:
	NodeContent nodeContent = NodeContent::INVALID;
	char _content;
	std::mutex contentMutex;
public:
	INodeContent(NodeContent content);
	void SetContent(NodeContent content);
	inline NodeContent GetContent() const { return nodeContent; }
	void Draw(Vector2 offset);
};