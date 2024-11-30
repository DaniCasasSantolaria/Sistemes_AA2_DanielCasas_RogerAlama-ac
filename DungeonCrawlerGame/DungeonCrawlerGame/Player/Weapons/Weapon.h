#pragma once
#include "../ICodable/ICodable.h"

enum class WeaponType {SWORD, SPEAR, INVALID};

class Weapon : public ICodable {
protected:
	WeaponType type = WeaponType::INVALID;
	int distanceAttack;
	int damage;
public:
	Json::Value Code() override;
	void Decode(Json::Value json) override;

	Weapon() = default;
	Weapon(int distance, int dmg)
		: distanceAttack(distance), damage(dmg) {}
	virtual int Attack() { return damage; };
	inline WeaponType GetWeaponType() { return type; }
};