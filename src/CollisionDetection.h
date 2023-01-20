#pragma once
#include "ChunkHandler.h"
#include "PlayerController.h"

class CollisionDetection
{
public:
	static void CheckChunkPlayerCollision(ChunkHandler* chunkHandler, PlayerController* playerController);
};