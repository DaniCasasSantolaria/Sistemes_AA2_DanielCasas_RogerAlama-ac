#pragma once
#include "../Vector2/Vector2.h"
#include "../ICodable/ICodable.h"
#include <mutex>

enum class NodeContent { WALL, ENEMY, OBJECT, NOTHING, PLAYER, PORTAL, CHEST, INVALID};

class INodeContent : public ICodable {
private:
	NodeContent nodeContent = NodeContent::INVALID;
	char _content;
	std::mutex contentMutex;
public:
	Json::Value Code() override;
	void Decode(Json::Value json) override;

	INodeContent(NodeContent content);
	void SetContent(NodeContent content);
	inline NodeContent GetContent() const { return nodeContent; }
	void Draw();
};