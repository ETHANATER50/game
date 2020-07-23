#pragma once
#include "core.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Transform.h"
#include <vector>
#include <string>

namespace ew {
	class Shape {
	public:
		Shape() {};
		Shape(const std::vector<ew::Vector2>& _points, const ew::Color& _color) { points = _points; color = _color; };

		bool load(const std::string& filename);

		void draw(Core::Graphics& graphics, ew::Vector2 position, float scale = 1.0f, float angle = 0.0f);
		void draw(Core::Graphics& graphics, const Transform& t);

		float getRadius() const { return radius; }

		void setColor(Color _color) { color = _color; };
		const Color& getColor() const { return color; };

	private:
		std::vector<ew::Vector2> points; 
		Color color;
		float radius;
	};


}

