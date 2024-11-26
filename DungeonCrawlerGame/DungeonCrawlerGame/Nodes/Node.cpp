#include "Node.h"
#include "../ConsoleControl/ConsoleControl.h"

Node::Node(Vector2 position, INodeContent* content) {
	_position = position;
	_content = content;
}

INodeContent* Node::GetContent() {
	return _content;
}

void Node::SetContent(NodeContent newContent) {
	_content->SetContent(newContent);
}

void Node::DrawContent() {
	if (_content == nullptr) {
		//CC::SetPosition(pos.x, pos.y);
		return;
	}

	_content->Draw();
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