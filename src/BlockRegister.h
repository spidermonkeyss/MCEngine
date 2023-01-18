#pragma once
#include "Blocks/AirBlock.h"
#include "Blocks/GrassBlock.h"
#include "Blocks/WoodBlock.h"
#include "Blocks/CobblestoneBlock.h"

#include <map>
#include <vector>

static class BlockRegister
{
private:
	template<typename T> static void RegisterBlock(Block::BlockID blockID);
	static void SetupShader();
	static void SetupTextureAtlas();
public:
	static std::map<Block::BlockID, std::unique_ptr<Block>> blockRegister;
	static void Init();
};