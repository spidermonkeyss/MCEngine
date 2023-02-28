//https://research.ncl.ac.uk/game/mastersdegree/gametechnologies/physicstutorials/1raycasting/Physics%20-%20Raycasting.pdf

#pragma once

#include "Math/Vector3.h"
#include "Blocks/Block.h"
#include "Chunk/ChunkHandler.h"

struct Ray
{
public:
	bool hit = false;
	Vector3 rPos;
	Vector3 rDir;
	float rLength;
	BlockData* block;
	BlockFace blockFace;
};

class RayCast 
{
public:
	static Ray Cast(Vector3 startPoint, Vector3 direction, float length, ChunkHandler* chunkHandler);
};