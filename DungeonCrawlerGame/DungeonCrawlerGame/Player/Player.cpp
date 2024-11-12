#include "Player.h"

Player::~Player() {
	for (Weapon* weapon : weapons)
		delete weapon;

	delete equipedWeapon;
}

void Player::Attack(EnemyDamageable* enemy) {
	equipedWeapon->Attack();
}

void Player::ReceiveDamage(int damage) {
	lifes -= damage;
}