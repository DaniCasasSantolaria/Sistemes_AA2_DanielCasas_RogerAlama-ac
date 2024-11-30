#pragma once

class PlayerDamageable {
public:
	virtual void ReceiveDamage(int damage) = 0;
};