#include "INodeContent.h"
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
	case NodeContent::OBJECT:
		_content = 'o';
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
	default:
		_content = '_';
		return;
	}
}

void INodeContent::SetContent(NodeContent content) {
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
	case NodeContent::OBJECT:
		_content = 'o';
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
	default:
		return;
	}
}

void INodeContent::Draw() {
	std::cout << _content;
}