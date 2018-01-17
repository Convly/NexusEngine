#ifndef NX_ENGINE__MODULE_MATHS_VECTOR2F_HPP_
#define NX_ENGINE__MODULE_MATHS_VECTOR2F_HPP_

#include <iostream>

namespace nx {
namespace maths {

struct Vector2f {
	/* Constructors / Destructors */
	Vector2f(double x_, double y_) : x(x_), y(y_) {}
	Vector2f(double value) : x(value), y(value) {}
    Vector2f(const Vector2f& other) : x(other.x), y(other.y) {}
	Vector2f() : x(0), y(0) {}
	~Vector2f() {}

	/* Members */
	double x;
	double y;

	/* Operators */
	Vector2f& operator=(const Vector2f& other) {
		if (this != &other) {
			x = other.x;
			y = other.y;
		}

		return *this;
	}

	Vector2f operator+(const Vector2f& other) {
		return Vector2f(x + other.x, y + other.y);
	}

	Vector2f operator+(const double k) {
		return Vector2f(x + k, y + k);
	}

	Vector2f& operator+=(const Vector2f& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector2f& operator+=(const double k) {
		x += k;
		y += k;
		return *this;
	}

	Vector2f operator-(const Vector2f& other) {
		return Vector2f(x - other.x, y - other.y);
	}

	Vector2f operator-(const double value) {
		return Vector2f(x - value, y - value);
	}

	Vector2f& operator-=(const Vector2f& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vector2f& operator-=(const double value) {
		x -= value;
		y -= value;
		return *this;
	}

	Vector2f operator*(const double value) {
		return Vector2f(x * value, y * value);
	}

	Vector2f& operator*=(const double value) {
		x *= value;
		y *= value;
		return *this;
	}

	Vector2f operator/(const double value) {
		return Vector2f(x / value, y / value);
	}

	Vector2f& operator/=(const double value) {
		x /= value;
		y /= value;
		return *this;
	}

	bool operator==(const Vector2f& other) {
		return x == other.x && y == other.y;
	}

	bool operator!=(const Vector2f& other) {
		return x != other.x || y != other.y;
	}

	/* Tools */

	void reset(const double value) {
		x = y = value;
	}

	void reset(const double x_, const double y_) {
		x = x_;
		y = y_;
	}

	void reset(void) {
		x = y = 0;
	}
};
    inline std::ostream& operator<<(std::ostream& os, const nx::maths::Vector2f& item) {
        std::cout << "v2f(" << item.x << ", " << item.y << ")";
        return os;
    }
}
}

#endif