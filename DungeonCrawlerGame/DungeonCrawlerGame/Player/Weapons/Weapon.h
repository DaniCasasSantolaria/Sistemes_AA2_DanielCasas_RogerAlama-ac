#pragma once
#include "../ICodable/ICodable.h"

class Weapon {
protected:
	int distanceAttack;
	int damage;
public:
	Json::Value Code() override;
	void Decode(Json::Value json) override;

	Weapon() = default;
	Weapon(int distance, int dmg)
		: distanceAttack(distance), damage(dmg) {}
	virtual int Attack() { return damage; };
};