#include "CollisionDetection.h"

#include "Collider.h"

void CollisionDetection::CheckChunkPlayerCollision(ChunkHandler* chunkHandler, PlayerController* playerController)
{
	//Get player position in chunk
	Vector3 playerChunkPosition = ChunkHandler::GetRelativeChunkPosition(playerController->GetCamera()->transform.position);

	//Get the points of collider in chunk space
	Vector3 start = (playerChunkPosition - (playerController->GetCollider().length / 2)) + playerController->GetCollider().offset;
	start = start + Vector3(0.5f, 0.5f, 0.5f);
	Vector3 ending = playerController->GetCollider().length;

	//Check which blocks player is in based on position
	//8 points up to 8 blocks collided
	BlockData* blocks[8];
	blocks[0] = &chunkHandler->originChunk->blocks[chunkHandler->originChunk->GetBlockIndex(start.x, start.y, start.z)];
	blocks[1] = &chunkHandler->originChunk->blocks[chunkHandler->originChunk->GetBlockIndex(start.x + ending.x, start.y, start.z)];
	blocks[2] = &chunkHandler->originChunk->blocks[chunkHandler->originChunk->GetBlockIndex(start.x + ending.x, start.y + ending.y, start.z)];
	blocks[3] = &chunkHandler->originChunk->blocks[chunkHandler->originChunk->GetBlockIndex(start.x, start.y + ending.y, start.z)];
	blocks[4] = &chunkHandler->originChunk->blocks[chunkHandler->originChunk->GetBlockIndex(start.x, start.y, start.z + ending.z)];
	blocks[5] = &chunkHandler->originChunk->blocks[chunkHandler->originChunk->GetBlockIndex(start.x + ending.x, start.y, start.z + ending.z)];
	blocks[6] = &chunkHandler->originChunk->blocks[chunkHandler->originChunk->GetBlockIndex(start.x + ending.x, start.y + ending.y, start.z + ending.z)];
	blocks[7] = &chunkHandler->originChunk->blocks[chunkHandler->originChunk->GetBlockIndex(start.x, start.y + ending.y, start.z + ending.z)];

	for (int i = 0; i < 8; i++)
	{
		if (blocks[i]->blockId != 0)
			std::cout << "Collision with block:" << blocks[i]->position.ToString() << std::endl;
	}
}
