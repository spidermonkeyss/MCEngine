#pragma once

#include "Vector3.h"
#include "glm/glm.hpp"

class Transform
{
public:
	Vector3 position;
	//Degrees
	Vector3 rotation;
	Vector3 scale;

	Transform();
	~Transform();

	void SetPosition(Vector3 pos);
	void SetPosition(float x, float y, float z);
	void SetRotation(Vector3 rot);
	void SetRotation(float x, float y, float z);
	void SetScale(Vector3 setScale);
	void SetScale(float x, float y, float z);

	Vector3 Forward();
	Vector3 Right();
	Vector3	Up();

	glm::mat4 GetTransformMatrix();
};