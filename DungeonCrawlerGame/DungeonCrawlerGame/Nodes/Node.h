#pragma once
#include "../Vector2/Vector2.h"
#include "INodeContent.h"
#include <mutex>

class Node : public ICodable {
private:
	Vector2 _position;
	std::mutex positionMutex;
	INodeContent* _content = nullptr;
	std::mutex _classMutex;
public:
	Json::Value Code() override;
	void Decode(Json::Value json) override;

	Node(Vector2 position, INodeContent* content);

	INodeContent* GetContent();
	template<typename T, typename = typename std::enable_if<std::is_base_of<INodeContent, T>::value>::type>
	T* GetContent() {
		T* contentCasted = dynamic_cast<T*>(_content);
		return contentCasted;
	}
	void SetContent(NodeContent newContent);
	void DrawContent(Vector2 offset);

	inline void SetPosition(Vector2 position) { _position = position; }
	inline Vector2 GetPosition() { 
		positionMutex.lock();
		Vector2 position;
		position.x = _position.x;
		position.y = _position.y;
		positionMutex.unlock();
		return position; 
	}
	inline INodeContent* GetINodeContent() { return _content; }
	bool IsEmpty();

	void Lock();
	void Unlock();
	inline ~Node() {
		delete _content;
	}
};