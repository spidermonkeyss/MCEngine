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
	void CheckLookingAtBlock(ChunkHandler* chunkHandler);
public:
	Entity* playerEntity;
	bool isLookingAtBlock = false;
	Vector3 blockLookingAtPos;
	Chunk* chunkLookingAt;
	BlockFace blockFaceLookingAt;

	void Update(ChunkHandler* chunkHandler);
	void SetCamera(Camera* camera);
	inline Camera* const GetCamera() const { return camera; }
};