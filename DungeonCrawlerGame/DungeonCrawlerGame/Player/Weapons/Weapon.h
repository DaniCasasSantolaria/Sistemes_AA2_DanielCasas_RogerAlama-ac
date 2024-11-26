#pragma once

class Weapon {
protected:
	int distanceAttack;
	int damage;
public:
	Weapon() = default;
	Weapon(int distance, int dmg)
		: distanceAttack(distance), damage(dmg) {}
	virtual int Attack() { return damage; };
};