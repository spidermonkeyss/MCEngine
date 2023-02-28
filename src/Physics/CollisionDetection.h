#pragma once
#include "Chunk/ChunkHandler.h"
#include "Collision.h"

#include <vector>

class CollisionDetection
{
private:
	static const float unit_circle_45_degrees;
	static void AABBCollision(ChunkHandler* chunkHandler, Entity* entity);
	static bool DoAABB(Entity* entity, BlockCollider blcokCollider);
	static bool DoAABBSweep(Entity* entity, BlockCollider blockCollider);
	static void CheckBlockCollider(Entity* entity, BlockCollider blockCollider);
	static void CheckBlockCollisionFace(BlockCollision* bc);
public:
	static const float minimum_collision_distance;
	static void CheckChunkEntityCollision(ChunkHandler* chunkHandler, List<Entity>* entities);
	static std::vector<BlockCollision> blockCollisionsToResolve;
	static std::vector<BlockCollision> blockCollisions;
};