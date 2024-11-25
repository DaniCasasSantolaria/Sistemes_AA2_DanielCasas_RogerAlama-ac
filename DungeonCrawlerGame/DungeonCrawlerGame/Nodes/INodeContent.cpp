#include "INodeContent.h"
#include "../ConsoleControl/ConsoleControl.h"

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
	case NodeContent::NOTHING:
		_content = ' ';
		break;
	default:
		return;
	}
}

void INodeContent::Draw(Vector2 offset) {
	CC::Lock();
	CC::SetPosition(offset.x, offset.y);
	std::cout << _content;
	CC::Unlock();
}