#pragma once
#include "Block.h"

class WoodBlock : public Block
{
public:
	WoodBlock()
	{
		blockID = BlockID::Wood;
		textureFilePath = "res/Textures/Blocks/wood_atlas.png";
	}
};