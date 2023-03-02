#pragma once
#include "ChunkMesh.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"

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
	glm::mat4 chunkMatrix4x4;
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
	int GetBlockIndex(int x, int y, int z);
	int GetBlockIndexInNeighborChunk(float x, float y, float z);
	Vector3 GetBlockWorldPosition(Vector3 vec);
	Vector3 GetBlockWorldPosition(float x, float y, float z);
	void RemoveBlock(int blockIndex);
	void RemoveBlock(float x, float y, float z);
	void RemoveBlock(Vector3 position);
	void ChangeBlock(int blockIndex, Block::BlockID blockId);
	void ChangeBlock(float x, float y, float z, Block::BlockID blockId);
	void ChangeBlock(Vector3 position, Block::BlockID blockId);
	void Empty();
};