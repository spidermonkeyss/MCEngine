#pragma once
#include "Math/Vector3.h"
#include "Blocks/Block.h"

struct BoxCollider
{
	Vector3 offset;
	Vector3 length;
};

struct BlockCollider
{
	Vector3 worldPosition;
	Vector3 startPoint;
	Vector3 endPoint;
	BlockData* block;
};