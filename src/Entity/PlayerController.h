#pragma once
#include "Input.h"
#include "Renderer/Camera.h"
#include "Entity.h"
#include "Physics/Physics.h"

class PlayerController
{
private:
	float mouseSpeed = 2.0f;
	float moveSpeed = 5.0f;
	Camera* camera;
	void CheckLookingAtBlock(ChunkHandler* chunkHandler);
public:
	Entity* playerEntity;
	bool isLookingAtBlock = false;
	Vector3 blockLookingAtChunkPos;
	Chunk* chunkLookingAt;
	BlockFace blockFaceLookingAt;

	Ray D_playerRay;

	void Update(ChunkHandler* chunkHandler);
	void SetCamera(Camera* camera);
	inline Camera* const GetCamera() const { return camera; }
};