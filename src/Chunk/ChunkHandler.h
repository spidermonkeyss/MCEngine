#pragma once
#include "Chunk.h"

class ChunkHandler
{
private:
	void LoadChunk(float x, float y);
	void UnloadChunk(unsigned int chunkIndex);

	void LoadChunks(Vector2 playerPos);
	void UnloadChunks();
	void UpdateChunks();
	void MarkNeighborChunksForUpdate(Chunk* chunk);
	void CheckOriginChunk(Vector3 playerPos);
public:
	int loadDistance = 5;
	int loadedChunks = 0;
	int chunkBufferSize = 0;

	Chunk* chunks;
	Chunk* originChunk;
	//List<Chunk> chunks;

	ChunkHandler();
	~ChunkHandler();
	
	void Update(Vector3 playerPos);
	Chunk* GetChunk(Vector2 vec);
	Chunk* GetChunk(float x, float y);
	Chunk* GetChunkFromWorldPosition(Vector3 vec);
	Chunk* GetChunkFromWorldPosition(float x, float y, float z);
	static Vector2 GetChunkPosition(Vector3 vec);
	static Vector2 GetChunkPosition(float x, float y, float z);
	static Vector3 GetRelativeChunkPosition(Vector3 vec);
	static Vector3 GetRelativeChunkPosition(float x, float y, float z);
};