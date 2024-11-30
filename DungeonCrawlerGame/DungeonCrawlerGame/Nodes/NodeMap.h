#pragma once
#include <vector>
#include <functional>
#include <mutex>
#include <list>
#include "Node.h"

class NodeMap : public ICodable {
public:
	typedef std::vector<Node*> NodeColumn;
	typedef std::vector<NodeColumn*> NodeGrid;

	typedef std::function<void(Node* node)> SafePick;
	typedef std::function<void(std::list<Node*> nodes)> SafeMultiPick;

private:
	Vector2 _offset;

	Vector2 _size;
	std::mutex _sizeMutex;

	NodeGrid _grid;
	std::mutex _gridMutex;

	std::mutex _safeMultiNodeLockMutex;

	Node* GetNode(Vector2 position);
public:
	NodeMap(Vector2 size, Vector2 offset);

	void CreatePortals(int numMap);
	Vector2 GetOffset();
	Vector2 GetSize();
	Json::Value Code() override;
	void Decode(Json::Value json) override;

	INodeContent* GetNodeContent(Vector2 position);
	void Draw();
	void SafePickNode(Vector2 position, SafePick safePickAction);
	void SafeMultiPickNode(std::list<Vector2> position, SafeMultiPick safeMultiPickAction);
	NodeGrid GetNodeGrid(NodeMap* nodeMap) { return nodeMap->_grid; }
	~NodeMap();

};