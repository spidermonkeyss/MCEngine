#include "Physics.h"
#include "CollisionDetection.h"

void Physics::PushEntityOutOfBlock(BlockCollision blockCollision)
{
	//Check east face 0,3,4,7
	if (blockCollision.playerColliderPoint == 0)
	{
	}
}

void Physics::BlockCollisions(std::vector<BlockCollision> blockCollisions)
{
	for (int i = 0; i < CollisionDetection::blockCollisions.size(); i++)
	{
		PushEntityOutOfBlock(blockCollisions[i]);
	}
}
