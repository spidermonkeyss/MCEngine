#include "ChunkHandler.h"

ChunkHandler::ChunkHandler()
{
	//Buffer extra chunks for chunk swapping
	chunkBufferSize = pow(loadDistance + loadDistance + 1, 2);
	chunks = new Chunk[chunkBufferSize];
}

ChunkHandler::~ChunkHandler()
{
}

void ChunkHandler::Update(Vector2 playerPos)
{
	//LoadChunks(Vector2(0, 0));
	LoadChunks(playerPos);
	UnloadChunks();
	UpdateChunks();
}

void ChunkHandler::LoadChunks(Vector2 playerPos)
{
	//reset chunk marks
	for (int i = 0; i < chunkBufferSize; i++)
	{
		chunks[i].isMarkedForUnload = true;
		chunks[i].isMarkedForUpdate = false;
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
Chunk* ChunkHandler::GetChunk(float x, float y)
{
	for (int i = 0; i < chunkBufferSize; i++)
	{
		if (chunks[i].isLoaded && chunks[i].chunkPos.x == x && chunks[i].chunkPos.y == y)
			return &chunks[i];
	}
	return nullptr;
}