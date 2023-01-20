#pragma once
#include "Input.h"
#include "Camera.h"
#include "Collider.h"

class PlayerController
{
private:
	float mouseSpeed = 2.0f;
	float moveSpeed = 15.0f;
	Camera* camera;
	Collider collider { Vector3(), Vector3(1, 1, 1) };
public:
	void Update();
	void SetCamera(Camera* camera);
	inline Camera* const GetCamera() const { return camera; }
	inline Collider GetCollider() { return collider; }
};