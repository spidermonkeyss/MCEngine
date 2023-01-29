#include "Physics.h"
#include "CollisionDetection.h"
#include "Time/TimeHandler.h"

void Physics::ResolveBlockCollision(BlockCollision blockCollision)
{
	float entityColliderDistanceToBlockCenter = blockCollision.entity->GetCollider().length.x + CollisionDetection::minimum_collision_distance;

	if (blockCollision.blockFaceCollidedWith == BlockCollision::top)// && blockCollision.entity->velocity.y < 0)
	{
		blockCollision.entity->velocity.y = 0;
		blockCollision.entity->transform.position.y = blockCollision.blockCollider.worldPosition.y + entityColliderDistanceToBlockCenter;
	}
	else if (blockCollision.blockFaceCollidedWith == BlockCollision::bot)// && blockCollision.entity->velocity.y > 0)
	{
		blockCollision.entity->velocity.y = 0;
		blockCollision.entity->transform.position.y = blockCollision.blockCollider.worldPosition.y - entityColliderDistanceToBlockCenter;
	}
	else if (blockCollision.blockFaceCollidedWith == BlockCollision::North)// && blockCollision.entity->velocity.z > 0)
	{
		blockCollision.entity->velocity.z = 0;
		blockCollision.entity->transform.position.z = blockCollision.blockCollider.worldPosition.z - entityColliderDistanceToBlockCenter;
	}
	else if (blockCollision.blockFaceCollidedWith == BlockCollision::South)// && blockCollision.entity->velocity.z < 0)
	{
		blockCollision.entity->velocity.z = 0;
		blockCollision.entity->transform.position.z = blockCollision.blockCollider.worldPosition.z + entityColliderDistanceToBlockCenter;
	}
	else if (blockCollision.blockFaceCollidedWith == BlockCollision::East)// && blockCollision.entity->velocity.x < 0)
	{
		blockCollision.entity->velocity.x = 0;
		blockCollision.entity->transform.position.x = blockCollision.blockCollider.worldPosition.x + entityColliderDistanceToBlockCenter;
	}
	else if (blockCollision.blockFaceCollidedWith == BlockCollision::West)// && blockCollision.entity->velocity.x > 0)
	{
		blockCollision.entity->velocity.x = 0;
		blockCollision.entity->transform.position.x = blockCollision.blockCollider.worldPosition.x - entityColliderDistanceToBlockCenter;
	}
}

void Physics::BlockCollisions(std::vector<BlockCollision> blockCollisions)
{
	for (int i = 0; i < CollisionDetection::blockCollisionsToResolve.size(); i++)
		ResolveBlockCollision(blockCollisions[i]);
}

void Physics::UpdatePositions(List<Entity>* entityList)
{
	for (int i = 0; i < entityList->Size(); i++)
		entityList->At(i)->transform.position = entityList->At(i)->transform.position + entityList->At(i)->velocity * TimeHandler::DeltaTime();
}
