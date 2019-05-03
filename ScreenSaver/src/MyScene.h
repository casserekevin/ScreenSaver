#pragma once
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
//glm includes
#include <GLM/glm.hpp>

#include <iostream>
#include <math.h>
#include <vector>

#include "Scene.h"

#include "Program.h"
#include "OpenGLErrors.h"
#include "Normal.h"
#include "Speed.h"
#include "LightFunction.h"
#include "Configuration.h"
#include "Camera.h"

#include "OBJClasses/OBJ.h"
#include "OBJClasses/Reader/MeshReader.h"


class MyScene : public Scene{

private:
	GLFWwindow* windowThatIsInserted;
	int width;
	int height;
	Configuration* configuration;

	Program* program;
	std::vector<OBJ* > objs;

	//-------------------------------------------------------
	//DADOS 
	//time
	float m_deltaTime = 0.0f;
	
	//model matrix
	Speed* speed = new Speed();

	float m_posicaoAtualX = 0.0f;
	float m_posicaoAtualY = 0.0f;
	
	Camera* camera;

	bool m_firstMouse = true;
	float m_lastX = (float)this->width / 2.0;
	float m_lastY = (float)this->height / 2.0;

	//---------------------------------------------------------

	//Funcoes:
	void processKeyboard() {
		this->camera->calculateSpeedRate(m_deltaTime);
		if (glfwGetKey(this->windowThatIsInserted, GLFW_KEY_W) == GLFW_PRESS) {
			this->camera->moveForward();
		}
		if (glfwGetKey(this->windowThatIsInserted, GLFW_KEY_S) == GLFW_PRESS) {
			this->camera->moveBackward();
		}
		if (glfwGetKey(this->windowThatIsInserted, GLFW_KEY_A) == GLFW_PRESS) {
			this->camera->moveLeft();
		}
		if (glfwGetKey(this->windowThatIsInserted, GLFW_KEY_D) == GLFW_PRESS) {
			this->camera->moveRight();
		}
	}
	void processKeyboardInput(int key, int scancode, int action, int mods) override {
		if (key == GLFW_KEY_ESCAPE) {
			switch (action) {
				case GLFW_PRESS:
					glfwSetWindowShouldClose(this->windowThatIsInserted, true);
					
					break;
			}
		}
	}
	void processMouseMovementInput(double xpos, double ypos) override {
		if (m_firstMouse)
		{
			m_lastX = xpos;
			m_lastY = ypos;
			m_firstMouse = false;
		}

		float xoffset = xpos - m_lastX;
		float yoffset = m_lastY - ypos; // reversed since y-coordinates go from bottom to top
		m_lastX = xpos;
		m_lastY = ypos;

		xoffset *= this->camera->getSensivity();
		yoffset *= this->camera->getSensivity();

		this->camera->calculateYawAngle(xoffset);
		this->camera->calculatePitchAngle(yoffset);

		this->camera->rotate();
	}
	void processMouseZoomInput(double xoffset, double yoffset) override {
		this->camera->calculateFOV(yoffset);

		glm::mat4 projectionMatrix = glm::perspective(glm::radians(this->camera->getFOV()), static_cast<float>(this->width) / static_cast<float>(this->height), 0.1f, 100.0f);
		program->sendMat4fv("projectionMatrix", projectionMatrix);
	}
	void processFrameBufferSize(int width, int height) override {
		this->width = width;
		this->height = height;
		glm::mat4 projectionMatrix = glm::perspective(glm::radians(this->camera->getFOV()), static_cast<float>(this->width) / static_cast<float>(this->height), 0.1f, 100.0f);
		program->sendMat4fv("projectionMatrix", projectionMatrix);
	}

public:
	//CONSTRUTORES
	MyScene(GLFWwindow* window, int width, int height, Configuration* configuration) : windowThatIsInserted(window), width(width), height(height), configuration(configuration), camera(configuration->getCamera()) {
		program = new Program("res/shaders/vertex.shader", "res/shaders/fragment.shader");

		MeshReader* meshReader = new MeshReader();
		for (int i = 0; i < this->configuration->getNumberOfData(); i++) {
			std::stringstream ss;
			ss << "res/obj/" << this->configuration->getOBJDataAt(i)->getFilepath();
			std::string pathfile = ss.str();
			OBJ* obj = new OBJ(meshReader->read(pathfile), this->configuration->getOBJDataAt(i), program); 
			objs.push_back(obj);
		}

		//Passagem da projection matrix
		glm::mat4 projectionMatrix = glm::perspective(glm::radians(this->camera->getFOV()), (float)this->width / (float)this->height, 0.1f, 100.0f);;
		program->sendMat4fv("projectionMatrix", projectionMatrix);
	}

	void update() override {
		glClearColor(0.5f, 0.5f, 1, 0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Passagem da view matrix
		program->sendMat4fv("viewMatrix", this->camera->generateViewMatrix());

		for (int i = 0; i < objs.size(); i++) {
			objs.at(i)->draw();
		}
		//---------------------------------------------------------
		//Lógica do tempo
		static float lastFrame = glfwGetTime();
		float currentFrame = glfwGetTime();
		m_deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;


		//Normal normal;
		//if ((m_rightPosition + m_posicaoAtualX) >= 1.0f) {
		//	normal.x = -1;
		//	normal.y = 0;
		//	LightReflection(normal, m_speed);
		//}
		//else if ((m_leftPosition + m_posicaoAtualX) <= -1.0f) {
		//	normal.x = 1;
		//	normal.y = 0;
		//	LightReflection(normal, m_speed);
		//}
		//if ((m_topPosition + m_posicaoAtualY) >= 1.0f) {
		//	normal.x = 0;
		//	normal.y = -1;
		//	LightReflection(normal, m_speed);
		//}
		//else if ((m_bottomPosition + m_posicaoAtualY) <= -1.0f) {
		//	normal.x = 0;
		//	normal.y = -1;
		//	LightReflection(normal, m_speed);
		//}

		//std::cout << "Posicao Atual X: " << m_posicaoAtualX << std::endl;
		//std::cout << "Posicao Atual Y: " << m_posicaoAtualY << std::endl;
		//std::cout << "Width: " << this->width << " Height: " << this->height << std::endl;
		//std::cout << "------------------------------------------------" << std::endl;
		////-------------------------------------------------------------------------------

		//glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_deltaTime * m_speed.x + m_posicaoAtualX, m_deltaTime * m_speed.y + m_posicaoAtualY, 0.0f));
		//program->sendMat4fv("modelMatrix", modelMatrix);
		//m_posicaoAtualX = glm::value_ptr(modelMatrix)[12];
		//m_posicaoAtualY = glm::value_ptr(modelMatrix)[13];
	}

	~MyScene() {}
};

