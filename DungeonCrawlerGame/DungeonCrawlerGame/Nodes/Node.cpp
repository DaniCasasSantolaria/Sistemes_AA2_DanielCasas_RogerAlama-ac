#include "Node.h"
#include "../ConsoleControl/ConsoleControl.h"

Json::Value Node::Code() {
	Json::Value nodeJson(Json::objectValue); // Objeto para las propiedades del nodo
	nodeJson["nodecontent"] = _content->Code();
	nodeJson["positionX"] = _position.x;
	nodeJson["positionY"] = _position.y;

	Json::Value classNode; // Envolver en un objeto con clave "node"
	classNode["node"] = nodeJson;

	return classNode;
}

void Node::Decode(Json::Value json) {
	if (json.isMember("nodecontent")) {
		_content->Decode(json["nodecontent"]);
	}

	if (json.isMember("positionX")) {
		_position.x = json["positionX"].asInt();
	}

	if (json.isMember("positionY")) {
		_position.y = json["positionY"].asInt();
	}
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
		std::cout << " ";
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