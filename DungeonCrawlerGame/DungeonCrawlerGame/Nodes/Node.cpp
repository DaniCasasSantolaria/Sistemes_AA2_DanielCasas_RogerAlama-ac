#include "Node.h"
#include "../ConsoleControl/ConsoleControl.h"

Json::Value Node::Code() {
	Json::Value json = _content->Code();
	json["positionX"] = _position.x;
	json["positionY"] = _position.y;
	return json;
}

void Node::Decode(Json::Value json) {
	_content->Decode(json["inodecontent"]);
	_position.x = json["positionX"].asInt();
	_position.y = json["positionY"].asInt();
}

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

void Node::DrawContent(Vector2 offset) {
	if (_content == nullptr) {
		Vector2 pos = offset + _position;
		//CC::SetPosition(pos.x, pos.y);
		_content->Draw(Vector2(pos.x, pos.y));
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