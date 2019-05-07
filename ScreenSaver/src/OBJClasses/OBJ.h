#pragma once

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include "Mesh.h"
#include "../Program.h"
#include "../OBJData.h"

#include "../Game.h"

class OBJ {
private:
	Mesh* mesh = nullptr;
	Program* program = nullptr;



	glm::mat4 modelMatrix;
public:

	OBJ(Mesh* mesh, OBJData* objData, Program* program, Game* game): mesh(mesh), program(program){
		this->mesh->setObjThatIsInserted(this);

		this->modelMatrix = glm::translate(glm::mat4(1.0f), objData->getPosition());

		game->updateActualPosition(this->modelMatrix[3].x, this->modelMatrix[3].y);
		game->addLimitsBox();
	}

	void draw() {
		program->sendMat4fv("modelMatrix", this->modelMatrix);
		this->mesh->draw(this->program);
	}

	void update(Game* game, Time* time) {
		time->calculateDelta();

		game->calculateSpeed();

		this->modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(time->getDelta() * game->getSpeed()->x + game->getActualPositionX(), time->getDelta() * game->getSpeed()->y + game->getActualPositionY(), 0.0f));
		game->updateActualPosition(this->modelMatrix[3].x, this->modelMatrix[3].y);
	}



	~OBJ() {}



	//GETTERS
	inline Mesh* getMesh() { return this->mesh; }
	inline glm::mat4 getModelMatrix() { return this->modelMatrix; }

	//SETTERS
};