#pragma once

#include "Normal.h"
#include "Speed.h"

class Light {
private:
	
public:
	Light(){}



	void calculateReflection(Normal normal, Speed* speed) {
		speed->x = -(2 * normal.x * (normal.x * speed->x + normal.y * speed->y) - speed->x);
		speed->y = -(2 * normal.y * (normal.x * speed->x + normal.y * speed->y) - speed->y);
	}

	~Light() {}
};
