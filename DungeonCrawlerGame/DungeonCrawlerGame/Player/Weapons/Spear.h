#pragma once
#include "Weapon.h"

class Spear : public Weapon {
public:
	Spear()
		: Weapon(2, 1) {
		type = WeaponType::SPEAR;
	}
	int Attack() /*override*/;
};