#include "Block.h"

int Block::debug_block_count = 0;
std::unique_ptr<Shader> Block::blockShader = nullptr;
std::unique_ptr<Texture> Block::blockTextureAtlas = nullptr;

Block::Block()
    : blockID(Block::BlockID::Grass)
{ 
	debug_block_count++; 
}
Block::~Block() 
{ 
	debug_block_count--; 
}