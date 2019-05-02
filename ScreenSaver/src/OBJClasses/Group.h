#pragma once

#include <GLEW/glew.h>
#include <GLM/glm.hpp>

#include <string>
#include <sstream>

#include "Face.h"
#include "../Program.h"
#include "../VertexBuffer.h"
#include "../Texture.h"

class Mesh;

class Group {
private:
	Mesh* meshThatIsInserted = nullptr;

	std::vector<Face*> faces;

	GLuint vaoID;

	Texture* texture = nullptr;
	std::string pathfileTexture;
	int numberOfVertices;

	//functions
	std::vector<glm::vec3> generatePositionData();
	std::vector<glm::vec2> generateTextureData();
	std::vector<glm::vec3> generateColorData();
public:
	Group(Mesh* mesh): meshThatIsInserted(mesh) {}

	void draw(Program* program) {
		program->send1i("texture0", this->texture->getTextureUnit());

		texture->bind();

		program->use();
		bindVAO();
		glDrawArrays(GL_TRIANGLES, 0, this->numberOfVertices);
		unbindVAO();
	}



	void addFace(Face* face) {
		this->faces.push_back(face);
	}



	void createVAOandTexture() {
		glGenVertexArrays(1, &this->vaoID);
		glBindVertexArray(this->vaoID);

		std::vector<glm::vec3> vec_positions = generatePositionData();
		VertexBuffer* vbo_position = new VertexBuffer(vec_positions.size() * sizeof(glm::vec3), vec_positions.data());
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		this->numberOfVertices = vec_positions.size();

		std::vector<glm::vec2> vec_textures = generateTextureData();
		VertexBuffer* vbo_texture = new VertexBuffer(vec_textures.size() * sizeof(glm::vec2), vec_textures.data());
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

		std::vector<glm::vec3> vec_colors = generateColorData();
		VertexBuffer* vbo_color = new VertexBuffer(vec_colors.size() * sizeof(glm::vec3), vec_colors.data());
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		unbindVAO();

		if (this->pathfileTexture == "\"\"") {
			texture = new Texture("res/textures/null.png", GL_TEXTURE_2D, 0);
		}
		else {
			std::stringstream ss;
			ss << "res/textures/" << this->pathfileTexture;
			this->pathfileTexture = ss.str();
			texture = new Texture(this->pathfileTexture.c_str(), GL_TEXTURE_2D, 0);
		}
		
	}

	void bindVAO() {
		glBindVertexArray(this->vaoID);
	}

	void unbindVAO() {
		glBindVertexArray(0);
	}



	~Group(){}



	//GETTERS

	//SETTERS
	void setPathFileTexture(std::string pathfile) { this->pathfileTexture = pathfile; }

};
