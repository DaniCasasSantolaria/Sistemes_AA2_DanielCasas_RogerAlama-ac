#include "Node.h"
#include "../ConsoleControl/ConsoleControl.h"

Node::Node(Vector2 position, INodeContent* content) {
	_position = position;
}

INodeContent* Node::GetContent() {
	return _content;
}

void Node::SetContent(NodeContent newContent) {
	_content->SetContent(newContent);
}

void Node::DrawContent(Vector2 offset) {
	if (_content == nullptr) {
		Vector2 pos = offset + _position;
		CC::Lock();
		CC::SetPosition(pos.x, pos.y);
		std::cout << " ";
		CC::Unlock();
		return;
	}

	_content->Draw(offset);
}

bool Node::IsEmpty() {
	if (_content == nullptr)
		return true;
	return false;
}

void Node::Lock() {
	_classMutex.lock();
}

void Node::Unlock() {
	_classMutex.unlock();
}