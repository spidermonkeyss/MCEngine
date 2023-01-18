#pragma once
#include "Input.h"
#include "Camera.h"

class PlayerController
{
private:
	float mouseSpeed = 2.0f;
	float moveSpeed = 15.0f;
	Camera* camera;
public:
	void Update();
	void SetCamera(Camera* camera);
};