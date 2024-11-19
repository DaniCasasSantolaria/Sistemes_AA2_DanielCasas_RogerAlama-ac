#include "NodeMap.h"

Node* NodeMap::UnSafeGetNode(Vector2 position) {
	if (position.x >= _size.x || position.y >= _size.y) {
		return nullptr;
	}
	NodeColumn* column = _grid[position.x];
	Node* node = (*column)[position.y];
	return node;
}

NodeMap::NodeMap(Vector2 size, Vector2 offset) {
	_size = size;
	_offset = offset;

	for (int x = 0; x < size.x; x++) {
		NodeColumn* column = new NodeColumn();

		for (int y = 0; y < size.y; y++) {
			column->push_back(new Node(Vector2(x, y)));
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

void NodeMap::Draw() {
	_gridMutex.lock();
	for (NodeColumn* column : _grid) {
		for (Node* node : *column) {
			node->Lock();
			node->DrawContent(_offset);
			node->Unlock();
		}
	}
	_gridMutex.unlock();
}

void NodeMap::SafePickNode(Vector2 position, SafePick safePickAction) {
	_sizeMutex.lock();
	_gridMutex.lock();
	Node* node = UnSafeGetNode(position);
	_gridMutex.unlock();
	_sizeMutex.unlock();

	node->Lock();
	safePickAction(node);
	node->Unlock();
}

void NodeMap::SafeMultiPickNode(std::list<Vector2> positions, SafeMultiPick safeMultiPickAction) {
	std::list<Node*> nodes = std::list<Node*>();

	_sizeMutex.lock();
	_gridMutex.lock();

	for (Vector2 pos : positions) {
		nodes.push_back(UnSafeGetNode(pos));
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