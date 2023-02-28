#pragma once
#include "Entity/Entity.h";
#include "Blocks/Block.h";

struct BlockCollision
{
	Entity* entity;
	BlockData* block;
	BlockCollider blockCollider;
	BlockFace blockFaceCollidedWith;
	bool resolve;
	bool canPushX = true;
	bool canPushY = true;
	bool canPushZ = true;
};