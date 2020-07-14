#include "pch.h"
#include "Shape.h"
#include "Math/Matrix22.h"

namespace ew {

	bool ew::Shape::load(const std::string& filename) {
		bool success = false;

		std::ifstream stream(filename);
		if (stream.is_open()) {
			success = true;

			stream >> color;

			std::string line;
			std::getline(stream, line);
			size_t size = stoi(line);
			
			for (size_t i = 0; i < size; i++) {
				Vector2 point;
				stream >> point;

				points.push_back(point);
			}

			stream.close();
		}
			return success;

	}
	void ew::Shape::draw(Core::Graphics& graphics, ew::Vector2 position, float scale, float angle) {
		graphics.SetColor(color);

		ew::Matrix22 mxScale;
		mxScale.scale(scale);

		ew::Matrix22 mxRotate;
		mxRotate.rotate(angle);

		ew::Matrix22 mx = mxScale * mxRotate;

		for (size_t i = 0; i < points.size() - 1; i++) {
			ew::Vector2 p1 = points[i];
			ew::Vector2 p2 = points[i + 1];

			p1 = p1 * mx;
			p2 = p2 * mx;



			p1 += position;
			p2 += position;

			graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}
	void Shape::draw(Core::Graphics& graphics, const Transform& t) {
		draw(graphics, t.position, t.scale, t.angle);
	}
}