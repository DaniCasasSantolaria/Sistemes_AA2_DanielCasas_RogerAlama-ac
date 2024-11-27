#include "NodeMap.h"
#include <iostream>
#include "../ConsoleControl/ConsoleControl.h"

Node* NodeMap::GetNode(Vector2 position) {
	_sizeMutex.lock();
	if (position.x >= _size.x || position.y >= _size.y) {
		_sizeMutex.unlock();
		return nullptr;
	}
	_sizeMutex.unlock();
	_gridMutex.lock();
	NodeColumn* column = _grid[position.x];
	_gridMutex.unlock();
	Node* node = (*column)[position.y];
	return node;
}

NodeMap::NodeMap(Vector2 size, Vector2 offset) {
	_size = size;
	_offset = offset;

	Vector2 randomNum1 = Vector2(rand() % ((8 - 1 + 1) + 1), rand() % ((8 - 1 + 1) + 1));
	Vector2 randomNum2 = Vector2(rand() % ((8 - 1 + 1) + 1), rand() % ((8 - 1 + 1) + 1));
	for (int x = 0; x < size.x; x++) {
		NodeColumn* column = new NodeColumn();

		for (int y = 0; y < size.y; y++) {
			if (x == 0 || y == 0 || x == size.x - 1 || y == size.y - 1) {
				if (x == size.x / 2 || y == size.y / 2)
					column->push_back(new Node(Vector2(x, y), new INodeContent(NodeContent::PORTAL)));
				else
				column->push_back(new Node(Vector2(x, y), new INodeContent(NodeContent::WALL)));
			}
			else if((x == randomNum1.x && y == randomNum1.y) || (x == randomNum2.x && y == randomNum2.y))
				column->push_back(new Node(Vector2(x, y), new INodeContent(NodeContent::WALL)));
			else
				column->push_back(new Node(Vector2(x, y), new INodeContent(NodeContent::NOTHING)));
		}
		_grid.push_back(column);
	}
}

Vector2 NodeMap::GetSize() {
	_sizeMutex.lock();
	Vector2 size = _size;
	_sizeMutex.unlock();
	return size;
}

INodeContent* NodeMap::GetNodeContent(Vector2 position) {
	_gridMutex.lock();
	NodeColumn* column = _grid[position.x];
	_gridMutex.unlock();
	Node* node = (*column)[position.y];
	return node->GetINodeContent();
}

Json::Value NodeMap::Code() {
	Json::Value json; // Objeto principal
	json["offsetX"] = _offset.x;
	json["offsetY"] = _offset.y;

	_sizeMutex.lock();
	json["sizeX"] = _size.x;
	json["sizeY"] = _size.y;
	_sizeMutex.unlock();

	Json::Value gridArray(Json::arrayValue);
	_gridMutex.lock();
	for (NodeColumn* column : _grid) {
		Json::Value nodesArray(Json::arrayValue);
		for (Node* node : *column) {
			node->Lock();
			nodesArray.append(node->Code());
			node->Unlock();
		}

		Json::Value columnJson; 
		columnJson["nodes"] = nodesArray;          
		gridArray.append(columnJson);              
	}
	_gridMutex.unlock();

	json["grid"] = gridArray;
	return json;
}

void NodeMap::Decode(Json::Value json) {
	_gridMutex.lock();

	Json::Value gridArray = json["grid"];
	int gridHeight = gridArray.size();
	_grid.resize(gridHeight);

	for (int i = 0; i < gridHeight; i++) {
		Json::Value columnJson = gridArray[i];

		Json::Value nodesArray = columnJson["nodes"];
		int columnWidth = nodesArray.size();


		NodeColumn* column = _grid[i];
		column->resize(columnWidth);

		for (int j = 0; j < columnWidth; j++) {
			Json::Value nodeJson = nodesArray[j];

			(*column)[j] = new Node(Vector2(0, 0), new INodeContent(NodeContent::INVALID));

			Node* node = (*column)[j];
			node->Lock();
			node->Decode(nodeJson["node"]);
			node->Unlock();
		}
	}
	_gridMutex.unlock();

	if (json.isMember("offsetX")) {
		_offset.x = json["offsetX"].asInt();
	}
	if (json.isMember("offsetY")) {
		_offset.y = json["offsetY"].asInt();
	}

	_sizeMutex.lock();
	if (json.isMember("sizeX")) {
		_size.x = json["sizeX"].asUInt();
	}
	if (json.isMember("sizeY")) {
		_size.y = json["sizeY"].asUInt();
	}
	_sizeMutex.unlock();
}

void NodeMap::Draw() {
	CC::Lock();
	CC::SetPosition(0, 0);
	_gridMutex.lock();
	for (NodeColumn* column : _grid) {
		for (Node* node : *column) {
			node->Lock();
			node->DrawContent();
			node->Unlock();
		}
		std::cout << std::endl;
	}
	_gridMutex.unlock();
	CC::Unlock();
}

void NodeMap::SafePickNode(Vector2 position, SafePick safePickAction) {
	Node* node = GetNode(position);

	node->Lock();
	safePickAction(node);
	node->Unlock();
}

void NodeMap::SafeMultiPickNode(std::list<Vector2> positions, SafeMultiPick safeMultiPickAction) {
	std::list<Node*> nodes = std::list<Node*>();
 
	_sizeMutex.lock();
	_gridMutex.lock();

	for (Vector2 pos : positions) {
		nodes.push_back(GetNode(pos));
	}

	_gridMutex.unlock();
	_sizeMutex.unlock();

	_safeMultiNodeLockMutex.lock();

	for (Node* node : nodes) {
		if (node != nullptr) {
			node->Lock();
		}
	}

	_safeMultiNodeLockMutex.unlock();

	safeMultiPickAction(nodes);

	for (Node* node : nodes) {
		if (node != nullptr) {
			node->Unlock();
		}
	}
}

void NodeMap::PrintMap() {
	/*for (NodeColumn* column : _grid) {

	}*/
}