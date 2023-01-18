#pragma once
#include "Block.h"

class AirBlock : public Block
{
public:
	AirBlock()
	{
		blockID = BlockID::Air;
	}
};