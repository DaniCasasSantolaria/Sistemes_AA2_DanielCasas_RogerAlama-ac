#pragma once
#include "Object.h"
#include "../Player/Player.h"
class Chest {
private:
	Object* object;
public:
	Chest(Object* object)
		: object(object) {}
	void OpenChest(Player* player);
	inline ~Chest() { delete object; }
};