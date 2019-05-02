#pragma once

#include <GLM/glm.hpp>

#include <string>

class OBJData {
private:
	std::string filename;

	glm::vec3 position;
public:

	OBJData(std::string filename, glm::vec3 position): filename(filename), position(position) {}

	//GETTERS
	inline std::string getFilepath() { return this->filename; }
	inline glm::vec3 getPosition() { return this->position; }
};
