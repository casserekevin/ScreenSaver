#pragma once

#include <GLM/glm.hpp>


#include <iostream>

#include "Group.h"

class OBJ;

class Mesh {
private:
	OBJ* objThatIsInserted = nullptr;
	
	std::vector<glm::vec3*> positions;
	std::vector<glm::vec2*> textures;
	std::vector<glm::vec3*> normals;

	Group* group = nullptr;

public:
	Mesh() {
		this->group = new Group(this);
	}

	void draw(Program* program) {
		this->group->draw(program);
		
	}



	void addVertice(float x, float y, float z) {
		this->positions.push_back(new glm::vec3(x, y, z));
	}
	void addVertice(glm::vec3* vertice) {
		this->positions.push_back(vertice);
	}

	void addTexture(float x, float y) {
		this->textures.push_back(new glm::vec2(x, y));
	}
	void addTexture(glm::vec2* texture) {
		this->textures.push_back(texture);
	}

	void addNormal(float x, float y, float z) {
		this->normals.push_back(new glm::vec3(x, y, z));
	}
	void addNormal(glm::vec3* normal) {
		this->normals.push_back(normal);
	}



	~Mesh() {}



	//GETTERS
	inline Group* getGroup() { return this->group; }
	inline glm::vec3* getPositionAt(int index) { return this->positions.at(index); }
	inline glm::vec3* getNormalAt(int index) { return this->normals.at(index); }
	inline glm::vec2* getTextureAt(int index) { return this->textures.at(index); }

	//SETTERS
	void setObjThatIsInserted(OBJ* obj) { this->objThatIsInserted = obj; }
};

