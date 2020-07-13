#pragma once

namespace ew {

	const float PI = 3.1415f;
	const float TWO_PI = PI * 2;
	const float HALF_PI = PI * 0.5f;

	inline float radiansToDregrees(float radians) {
		return radians * 180 / PI;
	}
	inline float degreesToRadians(float degrees) {
		return degrees * PI / 180;
	}

	template<typename T>
	inline T clamp(T v, T min, T max) {
		if (v < min) v = min;
		if (v > max) v = max;
		return v;
	}

	//template<>
	//inline Vector2 clamp(Vector2 v, Vector2 min, Vector2 max) {
	//	v.x = clamp(v.x, min.x, max.x);
	//	v.y = clamp(v.y, min.y, max.y);

	//	return v;
	//}

	template<typename T>
	inline T lerp(T a, T b, float t) {
		t = clamp(t, 0.0f, 1.0f);
		return (a + (b - a) * t);
	}
}
