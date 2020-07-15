#include "pch.h"
#include "Transform.h"

namespace ew {
	std::istream& operator>>(std::istream& stream, Transform& t) {
		stream >> t.position;

		std::string line;
		std::getline(stream, line);

		t.scale = stof(line);

		std::getline(stream, line);

		t.angle = stof(line);

		return stream;
	}

	void Transform::update() {
		ew::Matrix33 mxScale;
		mxScale.scale(scale);

		ew::Matrix33 mxRotate;
		mxRotate.rotate(angle);

		Matrix33 mxt;
		mxt.translate(position);

		matrix = mxScale * mxRotate * mxt;


	}

}
