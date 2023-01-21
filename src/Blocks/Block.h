#pragma once
#include "Math/Vector3.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

class Block
{
public:
	enum BlockID { Air, Grass, Wood, Cobblestone};
	
	BlockID blockID;
	std::string textureFilePath = "res/Textures/Blocks/test_atlas.png";

	static std::unique_ptr<Shader> blockShader;
	static std::unique_ptr<Texture> blockTextureAtlas;

	static int debug_block_count;

	Block();
	~Block();

	inline static std::string GetBlockShaderFilePath() { return "res/Shaders/BlockShader.shader"; }
};

struct BlockData
{
	Vector3 position;
	Block::BlockID blockId;
	float neighborIds[6];
};
