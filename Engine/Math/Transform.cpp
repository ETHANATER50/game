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

}
