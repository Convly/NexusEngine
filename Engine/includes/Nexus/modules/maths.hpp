#ifndef NX_ENGINE__MATHS_MODULE_HPP_
#define NX_ENGINE__MATHS_MODULE_HPP_

#include <iostream>

namespace nx {
	struct Vector2f {
		Vector2f(float x_, float y_) : x(x_), y(y_) {}
		Vector2f(float value) : x(value), y(value) {}

		float x;
		float y;

		Vector2f& operator+(const Vector2f& other) {
			this->x += other.x;
			this->y += other.y;
			return *this;
		}

		Vector2f& operator-(const Vector2f& other) {
			this->x -= other.x;
			this->y -= other.y;
			return *this;
		}

		bool operator==(const Vector2f& other) {
			return this->x == other.x && this->y == other.y;
		}

		bool operator!=(const Vector2f& other) {
			return this->x != other.x || this->y != other.y;
		}
	};
}

#endif