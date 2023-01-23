#include "Physics.h"
#include "CollisionDetection.h"

const float Physics::minimum_collision_distance = 0.00005f;

void Physics::PushEntityOutOfBlock(BlockCollision blockCollision)
{
	if (blockCollision.blockFaceCollidedWith == BlockCollision::top && blockCollision.entity->velocity.y < 0)
	{
		blockCollision.entity->velocity.y = 0;
		blockCollision.entity->transform.position.y = blockCollision.block->position.y + (1 - minimum_collision_distance);
	}
	else if (blockCollision.blockFaceCollidedWith == BlockCollision::bot && blockCollision.entity->velocity.y > 0)
	{
		blockCollision.entity->velocity.y = 0;
		blockCollision.entity->transform.position.y = blockCollision.block->position.y - (1 - minimum_collision_distance);
	}
	else if (blockCollision.blockFaceCollidedWith == BlockCollision::North && blockCollision.entity->velocity.z > 0)
	{
		blockCollision.entity->velocity.z = 0;
		blockCollision.entity->transform.position.z = blockCollision.block->position.z - (1 - minimum_collision_distance);
	}
	else if (blockCollision.blockFaceCollidedWith == BlockCollision::South && blockCollision.entity->velocity.z < 0)
	{
		blockCollision.entity->velocity.z = 0;
		blockCollision.entity->transform.position.z = blockCollision.block->position.z + (1 - minimum_collision_distance);
	}
	else if (blockCollision.blockFaceCollidedWith == BlockCollision::East && blockCollision.entity->velocity.x < 0)
	{
		blockCollision.entity->velocity.x = 0;
		blockCollision.entity->transform.position.x = blockCollision.block->position.x + (1 - minimum_collision_distance);
	}
	else if (blockCollision.blockFaceCollidedWith == BlockCollision::West && blockCollision.entity->velocity.x > 0)
	{
		blockCollision.entity->velocity.x = 0;
		blockCollision.entity->transform.position.x = blockCollision.block->position.x - (1 - minimum_collision_distance);
	}
}

void Physics::BlockCollisions(std::vector<BlockCollision> blockCollisions)
{
	for (int i = 0; i < CollisionDetection::blockCollisions.size(); i++)
	{
		PushEntityOutOfBlock(blockCollisions[i]);
	}
}
