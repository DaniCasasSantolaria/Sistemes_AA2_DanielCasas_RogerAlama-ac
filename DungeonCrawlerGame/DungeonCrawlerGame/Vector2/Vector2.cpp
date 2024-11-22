#include "Vector2.h"

Vector2 Vector2::operator+(Vector2 other) {
	Vector2 result = *this;
	result.x += other.x;
	result.y += other.y;
	return result;
}

Vector2 Vector2::operator-(Vector2 other) {
	Vector2 result = *this;
	result.x -= other.x;
	result.y -= other.y;
	return result;
}

Vector2 Vector2::operator+=(Vector2 other) {
	return *this + other;
}

Vector2 Vector2::operator-=(Vector2 other) {
	return *this - other;
}