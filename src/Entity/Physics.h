#pragma once
#include "Entity.h";
#include "Collision.h"

static class Physics
{
private:
	static const float minimum_collision_distance;
	static void PushEntityOutOfBlock(BlockCollision blockCollision);
public:
	static void BlockCollisions(std::vector<BlockCollision> blockCollisions);
};