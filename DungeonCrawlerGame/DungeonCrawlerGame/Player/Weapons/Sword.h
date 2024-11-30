#pragma once
#include "Weapon.h"

class Sword : public Weapon {
public:
	Sword()
		: Weapon(1, 1) {
		type = WeaponType::SWORD;
	}
	int Attack() /*override*/;
};