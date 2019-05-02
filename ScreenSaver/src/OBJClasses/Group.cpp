#pragma once

#include "Group.h"
#include "Mesh.h"

std::vector<glm::vec3> Group::generatePositionData() {
	std::vector<glm::vec3> vector;
	for (Face* face : this->faces) {
		for (int i = 0; i < face->getSizeOfFace(); i++) {
			vector.push_back(*(this->meshThatIsInserted->getPositionAt(face->getIndexPositionAt(i))));
		}
	}
	return vector;
}

std::vector<glm::vec2> Group::generateTextureData() {
	std::vector<glm::vec2> vector;
	for (Face* face : this->faces) {
		for (int i = 0; i < face->getSizeOfFace(); i++) {
			vector.push_back(*(this->meshThatIsInserted->getTextureAt(face->getIndexTextureAt(i))));
		}
	}
	return vector;
}

std::vector<glm::vec3> Group::generateColorData() {
	std::vector <glm::vec3> vector = {
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
	};
	return vector;
}

