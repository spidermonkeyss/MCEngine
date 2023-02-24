#include "CollisionDetection.h"
#include "Entity/Collider.h"

std::vector<BlockCollision> CollisionDetection::blockCollisionsToResolve;
std::vector<BlockCollision> CollisionDetection::blockCollisions;
const float CollisionDetection::unit_circle_45_degrees = 0.577350f;
const float CollisionDetection::minimum_collision_distance = 0.00001f;

void CollisionDetection::AABBCollision(ChunkHandler* chunkHandler, Entity* entity)
{
	blockCollisions.clear();
	//Get blocks near entity
	std::vector<BlockCollider> blockColliders;
	for (int y = -entity->GetCollider().length.y + entity->transform.position.y; y <= entity->GetCollider().length.y + entity->transform.position.y; y++)
	{
		for (int z = -entity->GetCollider().length.z + entity->transform.position.z; z <= entity->GetCollider().length.z + entity->transform.position.z; z++)
		{
			for (int x = -entity->GetCollider().length.x + entity->transform.position.x; x <= entity->GetCollider().length.x + entity->transform.position.x; x++)
			{
				//Create block colliders using world space
				BlockData* bd = chunkHandler->GetBlockFromWorldPosition(x, y, z);
				if (bd->blockId != 0)
				{
					BlockCollider bc;
					bc.block = bd;
					bc.worldPosition = Vector3(x, y, z);
					bc.startPoint = Vector3(x, y, z) - Vector3(0.5f, 0.5f, 0.5f);
					bc.endPoint = Vector3(x, y, z) + Vector3(0.5f, 0.5f, 0.5f);
					blockColliders.push_back(bc);
				}
			}
		}
	}

	//Check for collisions with nearby blocks
	for (int i = 0; i < blockColliders.size(); i++)
		CheckBlockCollider(entity, blockColliders[i]);
}

bool CollisionDetection::DoAABB(Entity* entity,  BlockCollider blockCollider)
{
	//Get the points of collider in chunk space
	Vector3 box1Start = (entity->transform.position - (entity->GetCollider().length / 2)) + entity->GetCollider().offset;
	Vector3 box1End = box1Start + entity->GetCollider().length;
	Vector3 box2Start = blockCollider.startPoint;
	Vector3 box2End = blockCollider.endPoint;

	if (box2Start.x <= box1End.x && box2End.x >= box1Start.x && box2End.y >= box1Start.y && box2Start.y <= box1End.y && box2Start.z <= box1End.z && box2End.z >= box1Start.z)
		return true;	
	return false;
}

bool CollisionDetection::DoAABBSweep(Entity* entity, BlockCollider blockCollider)
{
	entity->preVelocityTransform.position;
	entity->transform.position;
	blockCollider.worldPosition;
	return false;
}

void CollisionDetection::CheckBlockCollider(Entity* entity, BlockCollider blockCollider) 
{
	//Check for basic overlapping first
	if (DoAABB(entity, blockCollider))
	{
		BlockCollision bc;
		bc.blockCollider = blockCollider;
		bc.entity = entity;
		bc.resolve = true;

		/*-----If a collider exists on the same axis as another collider, the collider must only push on that axis-----*/
		/*-----If a collider exists on the same two axis, the collider wont resolve-----*/
		for (int i = 0; i < blockCollisions.size(); i++)
		{
			bool sameX = blockCollisions[i].blockCollider.worldPosition.x == blockCollider.worldPosition.x;
			bool sameY = blockCollisions[i].blockCollider.worldPosition.y == blockCollider.worldPosition.y;
			bool sameZ = blockCollisions[i].blockCollider.worldPosition.z == blockCollider.worldPosition.z;
			if (sameZ && sameY)
			{
				bc.canPushX = false;
				blockCollisions[i].canPushX = false;
			}
			if (sameX && sameZ)
			{
				bc.canPushY = false;
				blockCollisions[i].canPushY = false;
			}
			if (sameX && sameY)
			{
				bc.canPushZ = false;
				blockCollisions[i].canPushZ = false;
			}
		}

		blockCollisions.push_back(bc);
	}
	//Check sweep
	else if (DoAABBSweep(entity, blockCollider))
	{

	}
}

void CollisionDetection::CheckBlockCollisionFace(BlockCollision* bc)
{
	bc->blockFaceCollidedWith = BlockCollision::unresolved;
	
	Vector3 collisionNormalVec = (bc->entity->transform.position - bc->blockCollider.worldPosition).Normal();
	if (abs(collisionNormalVec.y) > abs(collisionNormalVec.x))
	{
		//y biggest
		if (abs(collisionNormalVec.y) > abs(collisionNormalVec.z) && bc->canPushY)
		{
			if (collisionNormalVec.y > 0)
				bc->blockFaceCollidedWith = BlockCollision::top;
			else
				bc->blockFaceCollidedWith = BlockCollision::bot;
		}
		//z biggest
		else if (bc->canPushZ)
		{
			if (collisionNormalVec.z > 0)
				bc->blockFaceCollidedWith = BlockCollision::South;
			else
				bc->blockFaceCollidedWith = BlockCollision::North;
		}
	}
	//z biggest
	else if (abs(collisionNormalVec.z) > abs(collisionNormalVec.x) && bc->canPushZ)
	{
		if (collisionNormalVec.z > 0)
			bc->blockFaceCollidedWith = BlockCollision::South;
		else
			bc->blockFaceCollidedWith = BlockCollision::North;
	}
	//x biggest
	else if (bc->canPushX)
	{
		if (collisionNormalVec.x > 0)
			bc->blockFaceCollidedWith = BlockCollision::East;
		else
			bc->blockFaceCollidedWith = BlockCollision::West;
	}

	if (bc->blockFaceCollidedWith == BlockCollision::unresolved)
		bc->resolve = false;
}

//Find all blocks entity is touching them determine which way to push the entity for resolution
//Doing this after getting all collisions fixes edge catching on blocks on the saem level
void CollisionDetection::CheckChunkEntityCollision(ChunkHandler* chunkHandler, List<Entity>* entities)
{
	blockCollisionsToResolve.clear();
	for (int i = 0; i < entities->Size(); i++)
		AABBCollision(chunkHandler, entities->At(i));

	//Add collisions to total collision
	for (int i = 0; i < blockCollisions.size(); i++)
	{
		//Check collision face after all collisions are checked
		CheckBlockCollisionFace(&blockCollisions[i]);
		if (blockCollisions[i].resolve)
			blockCollisionsToResolve.push_back(blockCollisions[i]);
	}
}