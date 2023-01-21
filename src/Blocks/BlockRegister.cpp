#include "BlockRegister.h"

#include <iostream>

std::map<Block::BlockID, std::unique_ptr<Block>> BlockRegister::blockRegister;

template<typename T> void BlockRegister::RegisterBlock(Block::BlockID blockID)
{
	if (std::is_base_of<Block, T>())
	{
		std::unique_ptr<Block> block(new T());
		blockRegister[blockID] = std::move(block);

		std::cout << "Registered Block:" << blockID << std::endl;
	}
	else
		std::cout << "Block type does not exist:" << blockID << std::endl;
}

void BlockRegister::SetupShader()
{
	//Create the block shader
	std::unique_ptr<Shader> shader(new Shader(Block::GetBlockShaderFilePath()));
	Block::blockShader = std::move(shader);
}

void BlockRegister::SetupTextureAtlas()
{
	//Create block texture atlas
	std::vector<unsigned char*> atlasBuffer;
	unsigned char* texBuffer = 0;
	int width = 384;
	int height = 64;
	int bpp = 3;
	int totalHeight = 0;
	int blockIndex = 0;
	for (int i = 0; i < blockRegister.size(); i++)
	{
		if ((Block::BlockID)i != Block::Air)
		{
			texBuffer = Texture::GetTexture(blockRegister.at((Block::BlockID)i)->textureFilePath, &width, &height, &bpp);
			if (width != 384 || height != 64 || bpp != 3)
			{
				std::cout << "WARNING!!! texture for blockid:" << (Block::BlockID)i << " did not have proper demensions. Could cause memory leak and textures might not line up properly" << std::endl;
			}
			atlasBuffer.resize(blockIndex + 1);
			atlasBuffer.at(blockIndex) = texBuffer;
			totalHeight += height;
			blockIndex++;
		}
	}
	int size = width * height * 4;
	unsigned char* buffer = new unsigned char[size * atlasBuffer.size()];
	for (int i = 0; i < atlasBuffer.size(); i++)
	{
		for (int k = 0; k < size; k++)
			buffer[(i * size) + k] = atlasBuffer.at(i)[k];
	}

	std::unique_ptr<Texture> textureAtlas(new Texture("res/Textures/Blocks/test_atlas.png", 0));
	textureAtlas->CreateTexture(buffer, width, totalHeight, bpp);
	Block::blockTextureAtlas = std::move(textureAtlas);

	//buffer gets freed in the CreateTexture function
	//delete[] buffer;
	
	if (texBuffer)
		free(texBuffer);
}

void BlockRegister::Init()
{
	RegisterBlock<AirBlock>(Block::BlockID::Air);
	RegisterBlock<GrassBlock>(Block::BlockID::Grass);
	RegisterBlock<WoodBlock>(Block::BlockID::Wood);
	RegisterBlock<CobblestoneBlock>(Block::BlockID::Cobblestone);
	
	std::cout << blockRegister.size() << " blocks registered" << std::endl;

	SetupShader();
	SetupTextureAtlas();
}