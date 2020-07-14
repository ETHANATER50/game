#pragma once
#include <cmath>
#include<iostream>

namespace ew {
	struct Vector2{
		float x, y;

		Vector2() :x{ 0 }, y{ 0 } {}
		Vector2(float x, float y) : x{ x }, y{ y } {}

		Vector2(int x, int y) : x{ static_cast<float> (x) }, y{ static_cast<float> (y) } {}

		float& operator [] (size_t index) { return (&x)[index]; }
		const float& operator [] (size_t index) const { return (&x)[index]; }

		void set(float x, float y) { this->x = x; this->y = y; }

		Vector2 operator + (const Vector2& v) const { return Vector2{ x + v.x, y + v.y }; }
		Vector2 operator - (const Vector2& v) const { return Vector2{ x - v.x, y - v.y }; }
		Vector2 operator * (const Vector2& v) const { return Vector2{ x * v.x, y * v.y }; }
		Vector2 operator / (const Vector2& v) const { return Vector2{ x / v.x, y / v.y }; }

		Vector2 operator + (float s) const { return Vector2{ x + s, y + s }; }
		Vector2 operator - (float s) const { return Vector2{ x - s, y - s }; }
		Vector2 operator * (float s) const { return Vector2{ x * s, y * s }; }
		Vector2 operator / (float s) const { return Vector2{ x / s, y / s }; }

		Vector2& operator += (float s) { x += s, y += s; return *this; }
		Vector2& operator -= (float s) { x -= s, y -= s; return *this; }
		Vector2& operator *= (float s) { x *= s, y *= s; return *this; }
		Vector2& operator /= (float s) { x /= s, y /= s; return *this; }

		Vector2& operator += (const Vector2& v) { x += v.x, y += v.y; return *this; }
		Vector2& operator -= (const Vector2& v) { x -= v.x, y -= v.y; return *this; }
		Vector2& operator *= (const Vector2& v) { x *= v.x, y *= v.y; return *this; }
		Vector2& operator /= (const Vector2& v) { x /= v.x, y /= v.y; return *this; }

		Vector2 operator - () { return Vector2{ -x, -y }; }

		friend std::istream& operator >> (std::istream& stream, Vector2& v);

		float length() const;
		float lengthSqr() const;

		Vector2 normalized() const;
		void normalize();

		static float distance(const Vector2& v1, const Vector2& v2);
		static Vector2 rotate(const Vector2& v,float radians);

		static const Vector2 left;
		static const Vector2 right;
		static const Vector2 up;
		static const Vector2 down;
		static const Vector2 forward;
	};

	inline float Vector2::length() const {
		return std::sqrt((x * x) + (y * y));
	}

	inline float Vector2::lengthSqr() const {
		return ((x * x) + (y * y));
	}

	inline Vector2 Vector2::normalized() const {
		float len = length();

		return (len == 0.0f) ? Vector2{ 0.0f, 0.0f } : *this / len;
	}

	inline void Vector2::normalize() {
		float len = length();
		if (len == 0) {
			x = y = 0;
		}
		else {
			*this /= len;
		}
	}

	inline float Vector2::distance(const Vector2& v1, const Vector2& v2) {
		Vector2 v = v1 - v2;

		return v.length();
	}

	inline Vector2 Vector2::rotate(const Vector2& v, float radians) {
		float x = v.x * std::cos(radians) - v.y * std::sin(radians);
		float y = v.x * std::sin(radians) + v.y * std::cos(radians);

		return Vector2{ x,y };
	}
}