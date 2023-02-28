#pragma once
#include "Entity/Entity.h";
#include "Collision.h"

struct Ray
{
public:
	bool hit = false;
	Vector3 rPos;
	Vector3 rDir;
	float rLength;
	Chunk* chunk;
	BlockData* block;
	BlockFace blockFace;
};

static class Physics
{
private:
	static void ResolveBlockCollision(BlockCollision blockCollision);
public:
	
	//https://research.ncl.ac.uk/game/mastersdegree/gametechnologies/physicstutorials/1raycasting/Physics%20-%20Raycasting.pdf
	static Ray CastRay(Vector3 startPoint, Vector3 direction, float length, ChunkHandler* chunkHandler);
	static void ResolveBlockCollisions(std::vector<BlockCollision> blockCollisions);
	static void UpdatePositions(List<Entity>* entityList);
};