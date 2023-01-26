#include "CollisionDetection.h"
#include "Entity/Collider.h"

std::vector<BlockCollision> CollisionDetection::blockCollisions;
const float CollisionDetection::unit_circle_45_degrees = 0.577350f;
const float CollisionDetection::minimum_collision_distance = 0.00001f;

void CollisionDetection::AABBCollision(ChunkHandler* chunkHandler, Entity* entity)
{
	//Get blocks near entity
	std::vector<BlockCollider> blockColliders;
	for (int x = -entity->GetCollider().length.x + entity->transform.position.x; x <= entity->GetCollider().length.x + entity->transform.position.x; x++)
	{
		for (int y = -entity->GetCollider().length.y + entity->transform.position.y; y <= entity->GetCollider().length.y + entity->transform.position.y; y++)
		{
			for (int z = -entity->GetCollider().length.z + entity->transform.position.z; z <= entity->GetCollider().length.z + entity->transform.position.z; z++)
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
	
	//Get the points of collider in chunk space
	Vector3 startPoint = (entity->transform.position - (entity->GetCollider().length / 2)) + entity->GetCollider().offset;
	Vector3 endPoint = startPoint + entity->GetCollider().length;

	//Check for collisions with nearby blocks
	for (int i = 0; i < blockColliders.size(); i++)
		DoSweptAABB(entity, blockColliders[i]);
}

bool CollisionDetection::DoAABB(Vector3 box1Start, Vector3 box1End, Vector3 box2Start, Vector3 box2End)
{
	if (box2Start.x <= box1End.x && box2End.x >= box1Start.x && box2End.y >= box1Start.y && box2Start.y <= box1End.y && box2Start.z <= box1End.z && box2End.z >= box1Start.z)
		return true;	
	return false;
}

void CollisionDetection::DoSweptAABB(Entity* entity, BlockCollider blockCollider) 
{
	//Get the points of collider in chunk space
	Vector3 startPoint = (entity->transform.position - (entity->GetCollider().length / 2)) + entity->GetCollider().offset;
	Vector3 endPoint = startPoint + entity->GetCollider().length;

	//Check for basic overlapping first
	if (DoAABB(startPoint, endPoint, blockCollider.startPoint, blockCollider.endPoint))
	{
		BlockCollision bc;
		bc.block = blockCollider.block;
		bc.entity = entity;

		Vector3 collisionNormalVec = (entity->transform.position - blockCollider.worldPosition).Normal();
		if (abs(collisionNormalVec.y) > abs(collisionNormalVec.x))
		{
			//y biggest
			if (abs(collisionNormalVec.y) > abs(collisionNormalVec.z))
			{
				if (collisionNormalVec.y > 0)
					bc.blockFaceCollidedWith = BlockCollision::top;
				else
					bc.blockFaceCollidedWith = BlockCollision::bot;
			}
			//z biggest
			else
			{
				if (collisionNormalVec.z > 0)
					bc.blockFaceCollidedWith = BlockCollision::South;
				else
					bc.blockFaceCollidedWith = BlockCollision::North;
			}
		}
		//z biggest
		else if (abs(collisionNormalVec.z) > abs(collisionNormalVec.x))
		{
			if (collisionNormalVec.z > 0)
				bc.blockFaceCollidedWith = BlockCollision::South;
			else
				bc.blockFaceCollidedWith = BlockCollision::North;
		}
		//x biggest
		else
		{
			if (collisionNormalVec.x > 0)
				bc.blockFaceCollidedWith = BlockCollision::East;
			else
				bc.blockFaceCollidedWith = BlockCollision::West;
		}

		blockCollisions.push_back(bc);
	}
	//Check sweep
	else
	{

	}
}

void CollisionDetection::CheckChunkEntityCollision(ChunkHandler* chunkHandler, List<Entity>* entities)
{
	blockCollisions.clear();
	for (int i = 0; i < entities->Size(); i++)
		AABBCollision(chunkHandler, entities->At(i));
}