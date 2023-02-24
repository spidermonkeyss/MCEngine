#pragma once
#include "Input.h"
#include "Renderer/Camera.h"
#include "Entity.h"

class PlayerController
{
private:
	float mouseSpeed = 2.0f;
	float moveSpeed = 5.0f;
	Camera* camera;
public:
	Entity* playerEntity;

	void Update();
	void SetCamera(Camera* camera);
	inline Camera* const GetCamera() const { return camera; }
};