#include "Weapon.h"

Json::Value Weapon::Code() {
	Json::Value json = Json::Value();
	json["distanceAttack"] = distanceAttack;
	json["damage"] = damage;
	return json;
}

void Weapon::Decode(Json::Value json) {
	distanceAttack = json["distanceAttack"].asUInt();
	damage = json["damage"].asUInt();
}