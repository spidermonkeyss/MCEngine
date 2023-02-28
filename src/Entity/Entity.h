#pragma once
#include "Physics/Collider.h"
#include "Transform.h"
#include "Chunk/ChunkHandler.h"
#include "List.h"

class Entity
{
private:
	EntityBoxCollider collider{ Vector3(), Vector3(1.0f, 1.0f, 1.0f) };
public:
	Transform transform;
	Transform preVelocityTransform;
	Vector3 velocity;
	Chunk* originChunk;

	bool isLoaded = false;

	Entity();
	~Entity();

	static void CheckOriginChunk(ChunkHandler* chunkHandler, List<Entity>* entityList);
	static void Gravity(List<Entity>* entityList);
	inline EntityBoxCollider GetCollider() { return collider; }
};