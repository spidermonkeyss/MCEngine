#pragma once
#include "Chunk.h"
#include "List.h"

class ChunkHandler
{
private:
	void LoadChunk(float x, float y);
	void UnloadChunk(unsigned int chunkIndex);

	void LoadChunks(Vector2 playerPos);
	void UnloadChunks();
	void UpdateChunks();
	void MarkNeighborChunksForUpdate(Chunk* chunk);
public:
	int loadDistance = 5;
	int loadedChunks = 0;
	int chunkBufferSize = 0;

	Chunk* chunks;
	//List<Chunk> chunks;

	ChunkHandler();
	~ChunkHandler();
	
	void Update(Vector2 playerPos);
	Chunk* GetChunk(float x, float y);
};