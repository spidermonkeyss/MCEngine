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

Ray Physics::BlockRayIntersect(Chunk* chunk, BlockData* bd, Vector3 startPoint, Vector3 direction)
{
	Ray ray;
	ray.hit = false;
	ray.block = nullptr;
	ray.chunk = nullptr;
	ray.blockFace = BlockFace::unresolved;
	ray.rLength = 0;

	//Check that block is not air
	if (bd->blockId != Block::Air)
	{
		Vector3 blockWorldPos = chunk->GetBlockWorldPosition(bd->position);
		if (bd->blockId != 0)
		{
			for (int face = 0; face < 6; face++)
			{
				//Check that the ray isnt paraelle with face
				Vector3 planeNormal = BlockFace::GetNormal((BlockFace::Face)face);
				float rayPlane_dot = Vector3::Dot(direction, planeNormal);

				if (rayPlane_dot != 0)
				{
					//Get shortest distance from startpoint to plane
					float d = 0;
					switch (face)
					{
					case 0://North
						d = abs(startPoint.z - (blockWorldPos.z - 0.5f));
						break;
					case 1://East
						d = abs(startPoint.x - (blockWorldPos.x + 0.5f));
						break;
					case 2://South
						d = abs(startPoint.z - (blockWorldPos.z + 0.5f));
						break;
					case 3://West
						d = abs(startPoint.x - (blockWorldPos.x - 0.5f));
						break;
					case 4://bot
						d = abs(startPoint.y - (blockWorldPos.y - 0.5f));
						break;
					case 5://top
						d = abs(startPoint.y - (blockWorldPos.y + 0.5f));
						break;
					default:
						break;
					}

					//Get ray length
					float t = d / abs(cos(Vector3::AngleRadians(direction, planeNormal)));
					if (t > 10)
					{
						std::cout << "t is big";
					}

					if (t < 0)
					{
						std::cout << std::endl;
						std::cout << "T IS NEG t:" << t << " d:" << d << " rad:" << Vector3::AngleRadians(direction, planeNormal) << std::endl;
						std::cout << "cos:" << abs(cos(Vector3::AngleRadians(direction, planeNormal))) << std::endl;
						std::cout << "blockWorldPos" << blockWorldPos.ToString() << std::endl;
						std::cout << "face" << face << std::endl;
						std::cout << std::endl;
						ASSERT(true);
					}

					//Get intersect point with plane
					Vector3 p = startPoint + (direction * t);

					//Check that point is on face
					Vector3 blockPointDifference = blockWorldPos - p;
					if (abs(blockPointDifference.x) <= 0.5f && abs(blockPointDifference.y) <= 0.5f && abs(blockPointDifference.z) <= 0.5f)
					{
						//if this is the first hit
						if (ray.hit == false)
						{
							ray.hit = true;
							ray.rLength = t;
							ray.rDir = direction;
							ray.rPos = startPoint;
							ray.blockFace = (BlockFace::Face)face;
							ray.block = bd;
							ray.chunk = chunk;
							ray.intersectPoint = p;
						}
						//Check if face intersect point is shortest length
						else if (t < ray.rLength)
						{
							ray.rLength = t;
							ray.rDir = direction;
							ray.rPos = startPoint;
							ray.blockFace = (BlockFace::Face)face;
							ray.block = bd;
							ray.chunk = chunk;
							ray.intersectPoint = p;
						}
					}
				}
			}
		}
	}

	return ray;
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

Ray Physics::CastRay(Vector3 startPoint, Vector3 direction, float length, ChunkHandler* chunkHandler)
{
	Ray ray;
	ray.hit = false;
	ray.block = nullptr;
	ray.chunk = nullptr;
	ray.blockFace = BlockFace::unresolved;
	ray.rLength = 0;

	direction = direction.Normal();

	//Set up ray bounding box
	Vector3 endPoint = startPoint + (direction * length);
	Vector3 rayBoundStart;
	rayBoundStart.x = std::round(std::min(startPoint.x, endPoint.x));
	rayBoundStart.y = std::round(std::min(startPoint.y, endPoint.y));
	rayBoundStart.z = std::round(std::min(startPoint.z, endPoint.z));
	Vector3 rayBoundEnd;
	rayBoundEnd.x = std::round(std::max(startPoint.x, endPoint.x));
	rayBoundEnd.y = std::round(std::max(startPoint.y, endPoint.y));
	rayBoundEnd.z = std::round(std::max(startPoint.z, endPoint.z));

	//Get all blocks in rays bounding box using world pos
	for (int y = rayBoundStart.y; y <= rayBoundEnd.y; y++)
	{
		for (int z = rayBoundStart.z; z <= rayBoundEnd.z; z++)
		{
			for (int x = rayBoundStart.x; x <= rayBoundEnd.x; x++)
			{
				BlockData* bd = chunkHandler->GetBlockFromWorldPosition(x, y, z);
				Chunk* chunk = chunkHandler->GetChunkFromWorldPosition(x, y, z);
				
				Ray blockRay = BlockRayIntersect(chunk, bd, startPoint, direction);

				if (blockRay.hit)
				{
					if (ray.hit == false)
						ray = blockRay;
					else if (blockRay.rLength < ray.rLength)
						ray = blockRay;
				}
			}
		}
	}

	return ray;
}