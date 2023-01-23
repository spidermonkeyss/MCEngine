#include "CollisionDetection.h"

#include "Entity/Collider.h"

std::vector<BlockCollision> CollisionDetection::blockCollisions;
std::vector<Vector3> CollisionDetection::entityColliderPoints(8);
const float CollisionDetection::unit_circle_45_degrees = 0.577350f;

void CollisionDetection::CheckChunkEntityCollision(ChunkHandler* chunkHandler, Entity* entities)
{
	blockCollisions.clear();


	for (int i = 0; i < Entity::MAX_ENTITIES; i++)
	{
		if (entities[i].isLoaded)
		{
			//Get player position in chunk
			Vector3 playerChunkPosition = ChunkHandler::GetRelativeChunkPosition(entities[i].transform.position);

			//Get the points of collider in chunk space
			Vector3 start = (playerChunkPosition - (entities[i].GetCollider().length / 2)) + entities[i].GetCollider().offset;
			start = start + Vector3(0.5f, 0.5f, 0.5f);
			Vector3 ending = entities[i].GetCollider().length;
			Chunk* chunk = chunkHandler->GetChunkFromWorldPosition(entities[i].transform.position);

			//Create collider points
			entityColliderPoints.at(0).SetVector(start.x, start.y, start.z);
			entityColliderPoints.at(1).SetVector(start.x + ending.x, start.y, start.z);
			entityColliderPoints.at(2).SetVector(start.x + ending.x, start.y + ending.y, start.z);
			entityColliderPoints.at(3).SetVector(start.x, start.y + ending.y, start.z);
			entityColliderPoints.at(4).SetVector(start.x, start.y, start.z + ending.z);
			entityColliderPoints.at(5).SetVector(start.x + ending.x, start.y, start.z + ending.z);
			entityColliderPoints.at(6).SetVector(start.x + ending.x, start.y + ending.y, start.z + ending.z);
			entityColliderPoints.at(7).SetVector(start.x, start.y + ending.y, start.z + ending.z);
			
			int blockIndex0 = chunk->GetBlockIndex(entityColliderPoints[0].x, entityColliderPoints[0].y, entityColliderPoints[0].z);
			int blockIndex1 = chunk->GetBlockIndex(entityColliderPoints[1].x, entityColliderPoints[1].y, entityColliderPoints[1].z);
			int blockIndex2 = chunk->GetBlockIndex(entityColliderPoints[2].x, entityColliderPoints[2].y, entityColliderPoints[2].z);
			int blockIndex3 = chunk->GetBlockIndex(entityColliderPoints[3].x, entityColliderPoints[3].y, entityColliderPoints[3].z);
			int blockIndex4 = chunk->GetBlockIndex(entityColliderPoints[4].x, entityColliderPoints[4].y, entityColliderPoints[4].z);
			int blockIndex5 = chunk->GetBlockIndex(entityColliderPoints[5].x, entityColliderPoints[5].y, entityColliderPoints[5].z);
			int blockIndex6 = chunk->GetBlockIndex(entityColliderPoints[6].x, entityColliderPoints[6].y, entityColliderPoints[6].z);
			int blockIndex7 = chunk->GetBlockIndex(entityColliderPoints[7].x, entityColliderPoints[7].y, entityColliderPoints[7].z);

			//Check which blocks player is in based on position
			//8 points up to 8 blocks collided
			BlockData* blocks[8];
			blocks[0] = (blockIndex0 != -1) ? &chunk->blocks[blockIndex0] : nullptr;
			blocks[1] = (blockIndex1 != -1) ? &chunk->blocks[blockIndex1] : nullptr;
			blocks[2] = (blockIndex2 != -1) ? &chunk->blocks[blockIndex2] : nullptr;
			blocks[3] = (blockIndex3 != -1) ? &chunk->blocks[blockIndex3] : nullptr;
			blocks[4] = (blockIndex4 != -1) ? &chunk->blocks[blockIndex4] : nullptr;
			blocks[5] = (blockIndex5 != -1) ? &chunk->blocks[blockIndex5] : nullptr;
			blocks[6] = (blockIndex6 != -1) ? &chunk->blocks[blockIndex6] : nullptr;
			blocks[7] = (blockIndex7 != -1) ? &chunk->blocks[blockIndex7] : nullptr;

			std::vector<BlockCollision> collisions;
			for (int i = 0; i < 8; i++)
			{
				if (blocks[i] != nullptr)
				{
					if (blocks[i]->blockId != 0)
					{
						BlockCollision bc;
						bc.block = blocks[i];
						bc.playerColliderPoint = entityColliderPoints[i];
						bc.entity = &entities[i];

						Vector3 collisionNormalVec = (playerChunkPosition - blocks[i]->position).Normal();
						if (collisionNormalVec.y > unit_circle_45_degrees)
							bc.blockFaceCollidedWith = BlockCollision::top;
						else if (collisionNormalVec.y < -unit_circle_45_degrees)
							bc.blockFaceCollidedWith = BlockCollision::bot;
						else if (collisionNormalVec.z > unit_circle_45_degrees)
							bc.blockFaceCollidedWith = BlockCollision::South;
						else if (collisionNormalVec.z < -unit_circle_45_degrees)
							bc.blockFaceCollidedWith = BlockCollision::North;
						else if (collisionNormalVec.x > unit_circle_45_degrees)
							bc.blockFaceCollidedWith = BlockCollision::East;
						else if (collisionNormalVec.x < -unit_circle_45_degrees)
							bc.blockFaceCollidedWith = BlockCollision::West;

						collisions.push_back(bc);
					}
				}
			}

			//Add these collisions to all collisions vector
			if (collisions.size() > 0)
			{
				for (int i = 0; i < collisions.size(); i++)
					blockCollisions.push_back(collisions[i]);
			}
		}
	}
}