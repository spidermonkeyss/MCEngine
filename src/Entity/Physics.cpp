#include "Physics.h"
#include "CollisionDetection.h"
#include "Time/TimeHandler.h"

void Physics::PushEntityOutOfBlock(BlockCollision blockCollision)
{
	float entityColliderDistanceToBlockCenter = blockCollision.entity->GetCollider().length.x - CollisionDetection::minimum_collision_distance;

	if (blockCollision.blockFaceCollidedWith == BlockCollision::top && blockCollision.entity->velocity.y < 0)
	{
		blockCollision.entity->velocity.y = 0;
		blockCollision.entity->transform.position.y = blockCollision.block->position.y + entityColliderDistanceToBlockCenter;
	}
	else if (blockCollision.blockFaceCollidedWith == BlockCollision::bot && blockCollision.entity->velocity.y > 0)
	{
		blockCollision.entity->velocity.y = 0;
		blockCollision.entity->transform.position.y = blockCollision.block->position.y - entityColliderDistanceToBlockCenter;
	}
	else if (blockCollision.blockFaceCollidedWith == BlockCollision::North && blockCollision.entity->velocity.z > 0)
	{
		blockCollision.entity->velocity.z = 0;
		blockCollision.entity->transform.position.z = blockCollision.block->position.z - entityColliderDistanceToBlockCenter;
	}
	else if (blockCollision.blockFaceCollidedWith == BlockCollision::South && blockCollision.entity->velocity.z < 0)
	{
		blockCollision.entity->velocity.z = 0;
		blockCollision.entity->transform.position.z = blockCollision.block->position.z + entityColliderDistanceToBlockCenter;
	}
	else if (blockCollision.blockFaceCollidedWith == BlockCollision::East && blockCollision.entity->velocity.x < 0)
	{
		blockCollision.entity->velocity.x = 0;
		blockCollision.entity->transform.position.x = blockCollision.block->position.x + entityColliderDistanceToBlockCenter;
	}
	else if (blockCollision.blockFaceCollidedWith == BlockCollision::West && blockCollision.entity->velocity.x > 0)
	{
		blockCollision.entity->velocity.x = 0;
		blockCollision.entity->transform.position.x = blockCollision.block->position.x - entityColliderDistanceToBlockCenter;
	}
}

void Physics::BlockCollisions(std::vector<BlockCollision> blockCollisions)
{
	for (int i = 0; i < CollisionDetection::blockCollisions.size(); i++)
	{
		PushEntityOutOfBlock(blockCollisions[i]);
	}
}

void Physics::UpdatePositions(List<Entity>* entityList)
{
	for (int i = 0; i < entityList->Size(); i++)
		entityList->At(i)->transform.position = entityList->At(i)->transform.position + entityList->At(i)->velocity * TimeHandler::DeltaTime();
}
