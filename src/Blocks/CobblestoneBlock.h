#pragma once
#include "Block.h"

class CobblestoneBlock : public Block
{
public:
	CobblestoneBlock()
	{
		blockID = BlockID::Cobblestone;
		textureFilePath = "res/Textures/Blocks/cobblestone_atlas.png";
	}
};