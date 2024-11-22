#pragma once

class Vector2 {
public:
	int x;
	int y;
	Vector2()
		: x(0), y(0) {}
	Vector2(int x, int y)
		: x(x), y(y) {}

	Vector2 operator+(Vector2 other);
	Vector2 operator-(Vector2 other);
	Vector2 operator+=(Vector2 other);
	Vector2 operator-=(Vector2 other);
};