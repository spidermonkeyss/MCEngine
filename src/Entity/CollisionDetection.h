#pragma once
#include "Chunk/ChunkHandler.h"
#include "Collision.h"

#include <vector>

class CollisionDetection
{
private:
	static const float unit_circle_45_degrees;
	static void AABBCollision(ChunkHandler* chunkHandler, Entity* entity);
	static bool DoAABB(Vector3 box1Start, Vector3 box1End, Vector3 box2Start, Vector3 box2End);
	static void CheckBlockCollider(Entity* entity, BlockCollider blockCollider);
	static void CheckBlockCollisionFace(Entity* entity, BlockCollision* bc);
public:
	static const float minimum_collision_distance;
	static void CheckChunkEntityCollision(ChunkHandler* chunkHandler, List<Entity>* entities);
	static std::vector<BlockCollision> blockCollisionsToResolve;
	static std::vector<BlockCollision> blockCollisions;
};