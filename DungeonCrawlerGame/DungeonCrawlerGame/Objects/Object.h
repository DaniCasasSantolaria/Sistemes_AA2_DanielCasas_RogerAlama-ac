#pragma once
enum class ObjectType {COIN, POTION};

class Object {
private:
	ObjectType type;
public:
	Object();
	inline ObjectType GetType() { return type; }
};