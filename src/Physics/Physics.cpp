#include "Physics.h"
#include "CollisionDetection.h"
#include "Time/TimeHandler.h"

void Physics::ResolveBlockCollision(BlockCollision blockCollision)
{
	float entityColliderDistanceToBlockCenter = blockCollision.entity->GetCollider().length.x + CollisionDetection::minimum_collision_distance;

	if (blockCollision.blockFaceCollidedWith == BlockFace::top)// && blockCollision.entity->velocity.y < 0)
	{
		blockCollision.entity->velocity.y = 0;
		blockCollision.entity->transform.position.y = blockCollision.blockCollider.worldPosition.y + entityColliderDistanceToBlockCenter;
	}
	else if (blockCollision.blockFaceCollidedWith == BlockFace::bot)// && blockCollision.entity->velocity.y > 0)
	{
		blockCollision.entity->velocity.y = 0;
		blockCollision.entity->transform.position.y = blockCollision.blockCollider.worldPosition.y - entityColliderDistanceToBlockCenter;
	}
	else if (blockCollision.blockFaceCollidedWith == BlockFace::North)// && blockCollision.entity->velocity.z > 0)
	{
		blockCollision.entity->velocity.z = 0;
		blockCollision.entity->transform.position.z = blockCollision.blockCollider.worldPosition.z - entityColliderDistanceToBlockCenter;
	}
	else if (blockCollision.blockFaceCollidedWith == BlockFace::South)// && blockCollision.entity->velocity.z < 0)
	{
		blockCollision.entity->velocity.z = 0;
		blockCollision.entity->transform.position.z = blockCollision.blockCollider.worldPosition.z + entityColliderDistanceToBlockCenter;
	}
	else if (blockCollision.blockFaceCollidedWith == BlockFace::East)// && blockCollision.entity->velocity.x < 0)
	{
		blockCollision.entity->velocity.x = 0;
		blockCollision.entity->transform.position.x = blockCollision.blockCollider.worldPosition.x + entityColliderDistanceToBlockCenter;
	}
	else if (blockCollision.blockFaceCollidedWith == BlockFace::West)// && blockCollision.entity->velocity.x > 0)
	{
		blockCollision.entity->velocity.x = 0;
		blockCollision.entity->transform.position.x = blockCollision.blockCollider.worldPosition.x - entityColliderDistanceToBlockCenter;
	}
}

void Physics::ResolveBlockCollisions(std::vector<BlockCollision> blockCollisions)
{
	for (int i = 0; i < CollisionDetection::blockCollisionsToResolve.size(); i++)
		ResolveBlockCollision(blockCollisions[i]);
}

void Physics::UpdatePositions(List<Entity>* entityList)
{
	for (int i = 0; i < entityList->Size(); i++)
	{
		entityList->At(i)->preVelocityTransform = entityList->At(i)->transform;
		entityList->At(i)->transform.position = entityList->At(i)->transform.position + entityList->At(i)->velocity * TimeHandler::DeltaTime();

		float distanceMoved = Vector3::Distance(entityList->At(i)->transform.position, entityList->At(i)->preVelocityTransform.position);
		Vector3 transformDiff;
		transformDiff.x = abs(entityList->At(i)->transform.position.x - entityList->At(i)->preVelocityTransform.position.x);
		transformDiff.y = abs(entityList->At(i)->transform.position.y - entityList->At(i)->preVelocityTransform.position.y);
		transformDiff.z = abs(entityList->At(i)->transform.position.z - entityList->At(i)->preVelocityTransform.position.z);

		//Revert movement if it is to much
		if (transformDiff.x > 0.45f)
			entityList->At(i)->transform.position.x	= entityList->At(i)->preVelocityTransform.position.x;
		if (transformDiff.y > 0.45f)
			entityList->At(i)->transform.position.y = entityList->At(i)->preVelocityTransform.position.y;
		if (transformDiff.z > 0.45f)
			entityList->At(i)->transform.position.z = entityList->At(i)->preVelocityTransform.position.z;
	}
}
