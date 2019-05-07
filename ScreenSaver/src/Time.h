#pragma once

#include <GLFW/glfw3.h>

class Time {
private:

	float delta;
public:
	Time() {}

	void calculateDelta() {
		static float lastFrame = glfwGetTime();
		float currentFrame = glfwGetTime();
		this->delta = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}



	~Time() {}



	//GETTERS
	inline float getDelta(){ return this->delta; }
};
