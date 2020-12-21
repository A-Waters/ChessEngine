#pragma once

#include <iostream>

struct Vector2
{
	char x, y;


	Vector2() {
		x = 0;
		y = 0;
	}

	Vector2(char in_x, char in_y) {
		x = in_x;
		y = in_y;
	}

	Vector2(const Vector2& other) {
		x = other.x;
		y = other.y;
	}




	bool isPosValid() {
		if (x > -1 && x < 8 && y < 8 && y >-1) {
			return true;
		}
		return false;
	}
};



inline std::ostream& operator<<(std::ostream& os, const Vector2& vec)
{
	os << "(" << (int)vec.x << ',' << (int)vec.y << ")";
	return os;
}