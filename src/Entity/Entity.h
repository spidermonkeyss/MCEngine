#pragma once
#include "Collider.h"
#include "Transform.h"
#include "Chunk/ChunkHandler.h"

class Entity
{
private:
	Collider collider{ Vector3(), Vector3(1, 1, 1) };
public:
	const static int MAX_ENTITIES;

	Transform transform;
	Vector3 velocity;
	Chunk* originChunk;

	bool isLoaded = false;

	Entity();
	~Entity();

	static void CheckOriginChunk(ChunkHandler* chunkHandler, Entity* entityList);
	static void UpdatePositions(Entity* entityList);
	inline Collider GetCollider() { return collider; }
};