#pragma once
#include "Entity.h";
#include "Collision.h"

static class Physics
{
private:
	static void PushEntityOutOfBlock(BlockCollision blockCollision);
public:
	static void BlockCollisions(std::vector<BlockCollision> blockCollisions);
};