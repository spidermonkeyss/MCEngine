#pragma once
#include "Chunk/ChunkHandler.h"
#include "Collision.h"

#include <vector>

class CollisionDetection
{
private:
	static const float unit_circle_45_degrees;
	static std::vector<Vector3> entityColliderPoints;
public:
	static void CheckChunkEntityCollision(ChunkHandler* chunkHandler, Entity* entities);
	static std::vector<BlockCollision> blockCollisions;
};