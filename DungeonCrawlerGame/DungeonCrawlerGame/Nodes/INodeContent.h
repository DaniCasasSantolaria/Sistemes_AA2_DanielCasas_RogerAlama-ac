#pragma once
#include "../Vector2/Vector2.h"
#include "../ICodable/ICodable.h"
#include <mutex>

enum class NodeContent { WALL, ENEMY, OBJECT, NOTHING, PLAYER, PORTAL, INVALID};

class INodeContent : public ICodable {
private:
	char _content;
	std::mutex contentMutex;
public:
	Json::Value Code() override;
	void Decode(Json::Value json) override;

	INodeContent(NodeContent content);
	void SetContent(NodeContent content);
	void Draw(Vector2 offset);
};