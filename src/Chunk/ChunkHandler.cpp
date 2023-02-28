#include "ChunkHandler.h"

#include "glm/gtc/matrix_transform.hpp"

ChunkHandler::ChunkHandler()
{
	//Buffer extra chunks for chunk swapping
	chunkBufferSize = pow(loadDistance + loadDistance + 1, 2);
	chunks = new Chunk[chunkBufferSize];
}

ChunkHandler::~ChunkHandler()
{
}

void ChunkHandler::Update(Vector3 playerPos)
{
	//LoadChunks(Vector2(0, 0));
	LoadChunks(Vector2(playerPos.x, playerPos.z));
	UnloadChunks();
	UpdateChunks();
}

void ChunkHandler::LoadChunks(Vector2 playerPos)
{
	//reset chunk marks
	for (int i = 0; i < chunkBufferSize; i++)
	{
		chunks[i].isMarkedForUnload = true;
	}

	Vector2 playerChunkPos = playerPos / Chunk::chunkWidth;
	playerChunkPos = Vector2(floor(playerChunkPos.x), floor(playerChunkPos.y));

	for (int y = playerChunkPos.y - loadDistance; y <= playerChunkPos.y + loadDistance; y++)
	{
		for (int x = playerChunkPos.x - loadDistance; x <= playerChunkPos.x + loadDistance; x++)
		{
			float dis = Vector2::Distance(playerPos, (Vector2(x * Chunk::chunkWidth + Chunk::chunkWidth / 2, y * Chunk::chunkWidth + Chunk::chunkWidth / 2)));
			if (dis <= loadDistance * Chunk::chunkWidth)
			{
				//Check if chunk is already loaded
				Chunk* chunk = GetChunk(x, y);
				if (chunk == nullptr)
					LoadChunk(x, y);
				//Keep the chunk loaded
				else
					chunk->isMarkedForUnload = false;
			}
		}
	}
}

void ChunkHandler::UnloadChunks()
{
	//Unload marked chunks
	for (int i = 0; i < chunkBufferSize; i++)
	{
		if (chunks[i].isLoaded && chunks[i].isMarkedForUnload)
			UnloadChunk(i);
	}
}

void ChunkHandler::UpdateChunks()
{
	//update chunk neighbors
	for (int i = 0; i < chunkBufferSize; i++)
	{
		if (chunks[i].isLoaded && chunks[i].isMarkedForUpdate)
		{
			chunks[i].neighborChunks[0] = GetChunk(chunks[i].chunkPos.x, chunks[i].chunkPos.y - 1.0f);//north
			chunks[i].neighborChunks[1] = GetChunk(chunks[i].chunkPos.x + 1.0f, chunks[i].chunkPos.y);//east
			chunks[i].neighborChunks[2] = GetChunk(chunks[i].chunkPos.x, chunks[i].chunkPos.y + 1.0f);//south
			chunks[i].neighborChunks[3] = GetChunk(chunks[i].chunkPos.x - 1.0f, chunks[i].chunkPos.y);//west
				 
			chunks[i].UpdateNeighborBlockIds(chunks[i].updateAllBlocks);
			chunks[i].chunkMesh.UpdateMesh(chunks[i].blocks);
			chunks[i].isMarkedForUpdate = false;
		}
	}
}

void ChunkHandler::MarkNeighborChunksForUpdate(Chunk* chunk)
{
	if (chunk->neighborChunks[0] != nullptr)
		chunk->neighborChunks[0]->isMarkedForUpdate = true;
	if (chunk->neighborChunks[1] != nullptr)
		chunk->neighborChunks[1]->isMarkedForUpdate = true;
	if (chunk->neighborChunks[2] != nullptr)
		chunk->neighborChunks[2]->isMarkedForUpdate = true;
	if (chunk->neighborChunks[3] != nullptr)
		chunk->neighborChunks[3]->isMarkedForUpdate = true;
}

void ChunkHandler::LoadChunk(float x, float y)
{
	//Check for empty slot
	for (int i = 0; i < chunkBufferSize; i++)
	{
		if (!chunks[i].isLoaded)
		{
			chunks[i].chunkPos = Vector2(x, y);
			chunks[i].chunkMatrix4x4 = glm::translate(glm::mat4(1.0f), glm::vec3(chunks[i].chunkPos.x * Chunk::chunkWidth, 0, chunks[i].chunkPos.y * Chunk::chunkWidth));
			chunks[i].GenerateBlocks();
				 
			chunks[i].isLoaded = true;
			chunks[i].isMarkedForUnload = false;
			chunks[i].isMarkedForUpdate = true;
			chunks[i].updateAllBlocks = true;

			//Set chunk neighbors
			chunks[i].neighborChunks[0] = GetChunk(x, y - 1.0f);//north
			chunks[i].neighborChunks[1] = GetChunk(x + 1.0f, y);//east
			chunks[i].neighborChunks[2] = GetChunk(x, y + 1.0f);//south
			chunks[i].neighborChunks[3] = GetChunk(x - 1.0f, y);//west

			loadedChunks++;

			MarkNeighborChunksForUpdate(&chunks[i]);
			return;
		}
	}

	std::cout << "No slots aviable. Chunk unloading not working right" << std::endl;
}

void ChunkHandler::UnloadChunk(unsigned int chunkIndex)
{
	chunks[chunkIndex].Empty();
	MarkNeighborChunksForUpdate(&chunks[chunkIndex]);
	loadedChunks--;
}

//Get loaded chunks
Chunk* ChunkHandler::GetChunk(Vector2 vec)
{
	return GetChunk(vec.x, vec.y);
}

//Get loaded chunks
Chunk* ChunkHandler::GetChunk(float x, float y)
{
	for (int i = 0; i < chunkBufferSize; i++)
	{
		if (chunks[i].isLoaded && chunks[i].chunkPos.x == x && chunks[i].chunkPos.y == y)
			return &chunks[i];
	}
	return nullptr;
}

//Get loaded chunks
Chunk* ChunkHandler::GetChunkFromWorldPosition(Vector3 vec)
{
	return GetChunk(GetChunkPosition(vec));
}

//Get loaded chunks
Chunk* ChunkHandler::GetChunkFromWorldPosition(float x, float y, float z)
{
	return GetChunk(GetChunkPosition(x, y, z));
}

BlockData* ChunkHandler::GetBlockFromWorldPosition(Vector3 vec)
{
	return GetBlockFromWorldPosition(vec.x, vec.y, vec.z);
}

BlockData* ChunkHandler::GetBlockFromWorldPosition(float x, float y, float z)
{
	Chunk* chunk = GetChunkFromWorldPosition(x, y, z);
	Vector3 pos = GetRelativeChunkPosition(x, y, z);
	return &chunk->blocks[chunk->GetBlockIndex(pos.x, pos.y, pos.z)];
}

Vector2 ChunkHandler::GetChunkPosition(Vector3 vec)
{
	return Vector2(floorf(vec.x / Chunk::chunkWidth), floorf(vec.z / Chunk::chunkWidth));
}

Vector2 ChunkHandler::GetChunkPosition(float x, float y, float z)
{
	return Vector2(floorf(x / Chunk::chunkWidth), floorf(z / Chunk::chunkWidth));
}

Vector3 ChunkHandler::GetRelativeChunkPosition(Vector3 vec)
{
	Vector2 chunkWorldPosition = GetChunkPosition(vec) * Chunk::chunkWidth;
	return Vector3(vec.x - chunkWorldPosition.x, vec.y, vec.z - chunkWorldPosition.y);
}

Vector3 ChunkHandler::GetRelativeChunkPosition(float x, float y, float z)
{
	Vector2 chunkWorldPosition = GetChunkPosition(x, y, z) * Chunk::chunkWidth;
	return Vector3(x - chunkWorldPosition.x, y, z - chunkWorldPosition.y);
}