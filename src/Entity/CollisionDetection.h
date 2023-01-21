#pragma once
#include "Chunk/ChunkHandler.h"
#include "Collision.h"

#include <vector>

class CollisionDetection
{
public:
	static void CheckChunkEntityCollision(ChunkHandler* chunkHandler, Entity* entities);
	static std::vector<BlockCollision> blockCollisions;
};