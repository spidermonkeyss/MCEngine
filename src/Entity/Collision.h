#pragma once
#include "Entity/Entity.h";
#include "Blocks/Block.h";

struct BlockCollision
{
	enum BlockFace { North, East, South, West, bot, top, unresolved };
	Entity* entity;
	//BlockData* block;
	BlockCollider blockCollider;
	BlockFace blockFaceCollidedWith;
	bool resolve;
	bool canPushX = true;
	bool canPushY = true;
	bool canPushZ = true;
};