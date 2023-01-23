#pragma once
#include "Entity/Entity.h";
#include "Blocks/Block.h";

struct BlockCollision
{
	enum BlockFace { North, East, South, West, bot, top };
	Entity* entity;
	BlockData* block;
	Vector3 playerColliderPoint;
	BlockFace blockFaceCollidedWith;
};