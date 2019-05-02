#pragma once

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include "Mesh.h"
#include "../Program.h"
#include "../OBJData.h"

class OBJ {
private:
	Mesh* mesh = nullptr;
	Program* program = nullptr;



	glm::vec3 position;
	glm::mat4 modelMatrix;
public:

	OBJ(Mesh* mesh, OBJData* objData, Program* program): mesh(mesh),  position(objData->getPosition()), program(program){
		this->mesh->setObjThatIsInserted(this);

		this->modelMatrix = glm::translate(glm::mat4(1.f), this->position);
	}

	void draw() {
		program->sendMat4fv("modelMatrix", this->modelMatrix);
		this->mesh->draw(this->program);
	}



	~OBJ() {}



	//GETTERS
	inline Mesh* getMesh() { return this->mesh; }
	inline glm::mat4 getModelMatrix() { return this->modelMatrix; }
};