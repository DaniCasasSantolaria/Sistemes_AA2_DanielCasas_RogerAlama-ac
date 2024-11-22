#pragma once

class Weapon {
private:
	int distanceAttack;
	int damage;
public:
	Weapon() = default;
	Weapon(int distance, int dmg)
		: distanceAttack(distance), damage(dmg) {}
	virtual void Attack() = 0;
};