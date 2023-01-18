#pragma once
#include "ChunkMesh.h"
#include "Vector2.h"

class Chunk
{
private:
	static unsigned int chunkIdCount;
	void NeighborBlockIdUpdate(int i);

	//used in block id updates
	int x, y, z;
	int north, east, south, west, bot, top;
public:
	static const int chunkWidth = 16;
	static const int chunkHeight = 256;
	static int chunkSize;

	Vector2 chunkPos;
	unsigned int id;
	bool isLoaded;

	bool isMarkedForUnload;
	bool isMarkedForUpdate;
	bool updateAllBlocks;

	BlockData* blocks;
	bool* isBorderBlocks;
	ChunkMesh chunkMesh;
	Chunk* neighborChunks[4];

	Chunk();
	~Chunk();
	
	void GenerateBlocks();
	void UpdateNeighborBlockIds(bool allBlocks);
	int GetBlockIndex(float x, float y, float z);
	int GetBlockIndexInNeighborChunk(float x, float y, float z);
	void Empty();
};