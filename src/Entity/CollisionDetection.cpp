#include "CollisionDetection.h"

#include "Entity/Collider.h"

std::vector<BlockCollision> CollisionDetection::blockCollisions;

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

			//Check which blocks player is in based on position
			//8 points up to 8 blocks collided
			BlockData* blocks[8];
			blocks[0] = &chunk->blocks[chunk->GetBlockIndex(start.x, start.y, start.z)];
			blocks[1] = &chunk->blocks[chunk->GetBlockIndex(start.x + ending.x, start.y, start.z)];
			blocks[2] = &chunk->blocks[chunk->GetBlockIndex(start.x + ending.x, start.y + ending.y, start.z)];
			blocks[3] = &chunk->blocks[chunk->GetBlockIndex(start.x, start.y + ending.y, start.z)];
			blocks[4] = &chunk->blocks[chunk->GetBlockIndex(start.x, start.y, start.z + ending.z)];
			blocks[5] = &chunk->blocks[chunk->GetBlockIndex(start.x + ending.x, start.y, start.z + ending.z)];
			blocks[6] = &chunk->blocks[chunk->GetBlockIndex(start.x + ending.x, start.y + ending.y, start.z + ending.z)];
			blocks[7] = &chunk->blocks[chunk->GetBlockIndex(start.x, start.y + ending.y, start.z + ending.z)];

			int blockCollisionCount = 0;
			for (int i = 0; i < 8; i++)
			{
				if (blocks[i]->blockId != 0)
					blockCollisionCount++;
			}

			if (blockCollisionCount > 0)
			{
				blockCollisions.resize(blockCollisions.size() + blockCollisionCount);

				int collisionIndex = 0;
				for (int i = 0; i < 8; i++)
				{
					if (blocks[i]->blockId != 0)
					{
						blockCollisions[collisionIndex].block = blocks[i];
						blockCollisions[collisionIndex].playerColliderPoint = i;
						blockCollisions[collisionIndex].entity = &entities[i];

						collisionIndex++;
					}
				}
			}
		}
	}
}