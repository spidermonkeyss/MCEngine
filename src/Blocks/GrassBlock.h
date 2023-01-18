#pragma once
#include "Block.h"

class GrassBlock : public Block
{
public:
	GrassBlock()
	{
		blockID = BlockID::Grass;
		textureFilePath = "res/Textures/Blocks/grass_atlas.png";
	}
};