#include "ChunkHandler.h"

ChunkHandler::ChunkHandler()
{
	//Buffer extra chunks for chunk swapping
	chunkBufferSize = pow(loadDistance + loadDistance + 1, 2);
	chunks.SetSize(chunkBufferSize);
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
	//for (int i = 0; i < loadedChunks; i++)
	for (Iterator chunk = &chunks; *chunk.Iterator_GetIndex() < loadedChunks; chunk.Iterator_Next())
	{
		chunk.Value().isMarkedForUnload = true;
		chunk.Value().isMarkedForUpdate = false;
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
	//for (int i = 0; i < loadedChunks; i++)
	//for (Iterator chunk = &chunks; chunk.Iterator_GetIndex() < loadedChunks; chunk.Iterator_Next())
	Iterator chunk = &chunks;
	while (*chunk.Iterator_GetIndex() < loadedChunks)
	{
		if (chunk.Value().isMarkedForUnload)
			UnloadChunk(*chunk.Iterator_GetIndex(), chunk);
		else
			chunk.Iterator_Next();
	}
}

void ChunkHandler::UpdateChunks()
{
	//update chunk neighbors
	//for (int i = 0; i < loadedChunks; i++)
	for (Iterator chunk = &chunks; *chunk.Iterator_GetIndex() < loadedChunks; chunk.Iterator_Next())
	{
		//Chunk* chunk = &chunks[i];
		if (chunk.Value().isMarkedForUpdate)
		{
			chunk.Value().neighborChunks[0] = GetChunk(chunk.Value().chunkPos.x, chunk.Value().chunkPos.y - 1.0f);//north
			chunk.Value().neighborChunks[1] = GetChunk(chunk.Value().chunkPos.x + 1.0f, chunk.Value().chunkPos.y);//east
			chunk.Value().neighborChunks[2] = GetChunk(chunk.Value().chunkPos.x, chunk.Value().chunkPos.y + 1.0f);//south
			chunk.Value().neighborChunks[3] = GetChunk(chunk.Value().chunkPos.x - 1.0f, chunk.Value().chunkPos.y);//west
				 
			chunk.Value().UpdateNeighborBlockIds(chunk.Value().updateAllBlocks);
			chunk.Value().chunkMesh.UpdateMesh(chunk.Value().blocks);
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
	loadedChunks++;

	Chunk* chunk = &chunks[loadedChunks - 1];

	chunk->chunkPos = Vector2(x, y);
	chunk->GenerateBlocks();
		 
	chunk->isLoaded = true;
	chunk->isMarkedForUnload = false;
	chunk->isMarkedForUpdate = true;
	chunk->updateAllBlocks = true;
	
	//Set chunk neighbors
	chunk->neighborChunks[0] = GetChunk(x, y - 1.0f);//north
	chunk->neighborChunks[1] = GetChunk(x + 1.0f, y);//east
	chunk->neighborChunks[2] = GetChunk(x, y + 1.0f);//south
	chunk->neighborChunks[3] = GetChunk(x - 1.0f, y);//west

	MarkNeighborChunksForUpdate(chunk);
}

void ChunkHandler::UnloadChunk(unsigned int chunkIndex, Iterator<Chunk> chunkIt)
{
	chunkIt.Value().Empty();
	chunkIt.Iterator_Next();
	*chunkIt.Iterator_GetIndex() -= 1;

	MarkNeighborChunksForUpdate(&chunks[chunkIndex]);
	loadedChunks--;
	//chunks.Swap(chunkIndex, loadedChunks);
	chunks.MoveBack(chunkIndex);
}

//Get loaded chunks
Chunk* ChunkHandler::GetChunk(float x, float y)
{
	//for (int i = 0; i < loadedChunks; i++)
	for (Iterator chunk = &chunks; *chunk.Iterator_GetIndex() < loadedChunks; chunk.Iterator_Next())
	{
		if (chunk.Value().chunkPos.x == x && chunk.Value().chunkPos.y == y)
			return &chunk.Value();
	}
	return nullptr;
}