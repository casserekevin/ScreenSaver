#pragma once

class Limits {
private:
	float top;
	float left;
	float bottom;
	float right;
public:
	Limits(float top, float left, float bottom, float right): top(top), left(left), bottom(bottom), right(right) {}



	~Limits() {}



	//GETTERS
	inline float getTop() { return this->top; }
	inline float getLeft() { return this->left; }
	inline float getBottom() { return this->bottom; }
	inline float getRight() { return this->right; }
};