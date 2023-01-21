#pragma once
#include "Collider.h"
#include "Transform.h"

class Entity
{
private:
	Collider collider{ Vector3(), Vector3(1, 1, 1) };
public:
	const static int MAX_ENTITIES;

	Transform transform;

	bool isLoaded = false;

	Entity();
	~Entity();

	inline Collider GetCollider() { return collider; }
};