#pragma once

#include <windows.h>

namespace ew {
	struct Color {
		float r, g, b;

		Color() : r{ 0 }, g{ 0 }, b{ 0 } {};
		Color(float r, float g, float b) : r{ r }, g{ g }, b{ b } {};

		float& operator [] (size_t index) { return (&r)[index]; }
		const float& operator [] (size_t index) const { return (&r)[index]; }

		void set(float _r, float _g, float _b) { r = _r; g = _g; b = _b; }

		Color operator + (const Color& c) const { return Color{ r + c.r, g + c.g, b + c.b }; }
		Color operator - (const Color& c) const { return Color{ r - c.r, g - c.g, b - c.b }; }
		Color operator * (const Color& c) const { return Color{ r * c.r, g * c.g, b * c.b }; }
		Color operator / (const Color& c) const { return Color{ r / c.r, g / c.g, b / c.b }; }

		Color operator + (float s) const { return Color{ r + s, g + s, b + s }; }
		Color operator - (float s) const { return Color{ r - s, g - s, b - s }; }
		Color operator * (float s) const { return Color{ r * s, g * s, b * s }; }
		Color operator / (float s) const { return Color{ r / s, g / s, b / s }; }
		
		Color& operator += (float s) { r += s, g += s, b += s; return *this; }
		Color& operator -= (float s) { r -= s, g -= s, b -= s; return *this; }
		Color& operator *= (float s) { r *= s, g *= s, b *= s; return *this; }
		Color& operator /= (float s) { r /= s, g /= s, b /= s; return *this; }
		
		Color& operator += (const Color& c) { r += c.r, g += c.g, b += c.b; return *this; }
		Color& operator -= (const Color& c) { r -= c.r, g -= c.g, b -= c.b; return *this; }
		Color& operator *= (const Color& c) { r *= c.r, g *= c.g, b *= c.b; return *this; }
		Color& operator /= (const Color& c) { r /= c.r, g /= c.g, b /= c.b; return *this; }

		friend std::istream& operator >> (std::istream& stream, Color& c);

		COLORREF pack888() const;

		operator COLORREF() const { return pack888(); }

	};

	inline COLORREF Color::pack888() const {
		BYTE _r = static_cast<BYTE>(r * 255.0f);
		BYTE _g = static_cast<BYTE>(g * 255.0f);
		BYTE _b = static_cast<BYTE>(b * 255.0f);

		return _r | (_g << 8) | (_b << 16);
	}
}