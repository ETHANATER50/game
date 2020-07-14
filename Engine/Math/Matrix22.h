#pragma once
#include "Vector2.h"

namespace ew {
	struct Matrix22 {
		float m[2][2];

		Matrix22() {}
		Matrix22(const Vector2& column1, const Vector2& column2) {
			m[0][0] = column1[0]; m[1][0] = column2[0];
			m[0][1] = column1[1]; m[1][1] = column2[1];
		}

		void scale(float s) {
			m[0][0] = s; m[1][0] = 0;
			m[0][1] = 0; m[1][1] = s;
		}

		void scale(float s1, float s2) {
			m[0][0] = s1; m[1][0] = 0;
			m[0][1] = 0; m[1][1] = s2;
		}

		void scale(const Vector2& v) {
			m[0][0] = v.x; m[1][0] = 0;
			m[0][1] = 0; m[1][1] = v.y;
		}

		void rotate(float angle) {
			m[0][0] = cos(angle); m[1][0] = sin(angle);
			m[0][1] = -sin(angle); m[1][1] = cos(angle);
		}


	};
}