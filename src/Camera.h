#pragma once

#include "Transform.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera
{
private:
	glm::mat4 proj;
public:
	Transform transform;
	float aspectRatio;
	float widthView;

	Camera();
	~Camera();

	void Init();

	inline glm::mat4* GetProjMat() { return &proj; }
};