#pragma once
#include "Entity.h";
#include "Collision.h"

static class Physics
{
private:
	static void ResolveBlockCollision(BlockCollision blockCollision);
public:
	static void ResolveBlockCollisions(std::vector<BlockCollision> blockCollisions);
	static void UpdatePositions(List<Entity>* entityList);
};