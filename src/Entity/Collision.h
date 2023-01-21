#pragma once

#include "Entity/Entity.h";
#include "Blocks/Block.h";

struct BlockCollision
{
	Entity* entity;
	BlockData* block;
	int playerColliderPoint;
};