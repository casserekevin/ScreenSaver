#pragma once

#include "Limits.h"
#include "Speed.h"
#include "Normal.h"
#include "Light.h"


class Game {
private:
	Limits* limitsObject;
	Limits* limitsBox;

	float posicaoAtualX;
	float posicaoAtualY;

	Speed* speed = new Speed();

	Light* light = new Light();
public:
	Game() {}

	void addLimitsObject(float top, float left, float bottom, float right) {
		this->limitsObject = new Limits(top, left, bottom, right);
	}

	void updateActualPosition(float x, float y) {
		this->posicaoAtualX = x;
		this->posicaoAtualY = y;
	}

	void addLimitsBox() {
		this->limitsBox = new Limits(this->posicaoAtualY + 1, this->posicaoAtualX - 1, this->posicaoAtualY - 1, this->posicaoAtualX + 1);
	}



	void calculateSpeed() {
		Normal normal;
		if ((this->posicaoAtualX + this->limitsObject->getRight()) >= this->limitsBox->getRight()) {
			normal.x = -1;
			normal.y = 0;
			light->calculateReflection(normal, this->speed);
		}
		else if ((this->posicaoAtualX + this->limitsObject->getLeft()) <= this->limitsBox->getLeft()) {
			normal.x = 1;
			normal.y = 0;
			light->calculateReflection(normal, this->speed);
		}
		if ((this->posicaoAtualY + this->limitsObject->getTop()) >= this->limitsBox->getTop()) {
			normal.x = 0;
			normal.y = -1;
			light->calculateReflection(normal, this->speed);
		}
		else if ((this->posicaoAtualY + this->limitsObject->getBottom()) <= this->limitsBox->getBottom()) {
			normal.x = 0;
			normal.y = -1;
			light->calculateReflection(normal, this->speed);
		}
	}



	~Game() {}



	//GETTERS
	inline float getActualPositionX() { return this->posicaoAtualX; }
	inline float getActualPositionY() { return this->posicaoAtualY; }
	inline Speed* getSpeed() { return this->speed; }
	inline Limits* getLimitsObject() { return this->limitsObject; }
	inline Limits* getLimitsBox() { return this->limitsBox; }
};
