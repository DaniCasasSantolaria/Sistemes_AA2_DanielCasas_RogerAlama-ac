#include "INodeContent.h"
#include "../ConsoleControl/ConsoleControl.h"
#include <iostream>

Json::Value INodeContent::Code() {
	Json::Value json = Json::Value();
	json["content"] = _content;
	return json;
}

void INodeContent::Decode(Json::Value json) {
	if (json.isMember("content")) {
		int content = json["content"].asInt();
		_content = (char)content;
	}
}

INodeContent::INodeContent(NodeContent content) {
	nodeContent = content;
	switch (content) {
	case NodeContent::PLAYER:
		_content = 'J';
		break;
	case NodeContent::WALL:
		_content = 'X';
		break;
	case NodeContent::ENEMY:
		_content = 'E';
		break;
	case NodeContent::PORTAL:
		_content = '#';
		break;
	case NodeContent::CHEST:
		_content = '?';
		break;
	case NodeContent::NOTHING:
		_content = ' ';
		break;
	case NodeContent::POTION:
		_content = 'P';
		break;
	case NodeContent::COIN:
		_content = 'C';
		break;
	default:
		_content = '_';
		return;
	}
}

void INodeContent::SetContent(NodeContent content) {
	nodeContent = content;
	switch (nodeContent) {
	case NodeContent::PLAYER:
		_content = 'J';
		break;
	case NodeContent::WALL:
		_content = 'X';
		break;
	case NodeContent::ENEMY:
		_content = 'E';
		break;
	case NodeContent::PORTAL:
		_content = 'P';
		break;
	case NodeContent::CHEST:
		_content = '?';
		break;
	case NodeContent::NOTHING:
		_content = ' ';
		break;
	case NodeContent::POTION:
		_content = 'P';
		break;
	case NodeContent::COIN:
		_content = 'C';
		break;
	default:
		return;
	}
}

void INodeContent::Draw(Vector2 offset) {
	CC::Lock();
	CC::SetPosition(offset.x, offset.y);
	switch (nodeContent) {
	case NodeContent::PLAYER:
		CC::SetColor(CC::CYAN);
		break;
	case NodeContent::WALL:
		CC::SetColor(CC::DARKGREEN);
		break;
	case NodeContent::ENEMY:
		CC::SetColor(CC::RED);
		break;
	case NodeContent::PORTAL:
		CC::SetColor(CC::DARKMAGENTA);
		break;
	case NodeContent::CHEST:
		CC::SetColor(CC::LIGHTGREY);
		break;
	case NodeContent::NOTHING:
		CC::SetColor(CC::WHITE);
		break;
	case NodeContent::POTION:
		CC::SetColor(CC::BLUE);
		break;
	case NodeContent::COIN:
		CC::SetColor(CC::YELLOW);
		break;
	default:
		CC::SetColor(CC::WHITE);
		break;
	}
	std::cout << _content;
	CC::SetColor(CC::WHITE);
	CC::Unlock();
}