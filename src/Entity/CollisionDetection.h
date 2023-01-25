#pragma once
#include "Chunk/ChunkHandler.h"
#include "Collision.h"

#include <vector>

class CollisionDetection
{
private:
	static const float unit_circle_45_degrees;
	static std::vector<BlockCollision> AABBCollision(ChunkHandler* chunkHandler, Entity* entity);
	static bool IsAABB(Vector3 box1Start, Vector3 box1End, Vector3 box2Start, Vector3 box2End);
public:
	static const float minimum_collision_distance;
	static void CheckChunkEntityCollision(ChunkHandler* chunkHandler, List<Entity>* entities);
	static std::vector<BlockCollision> blockCollisions;
};