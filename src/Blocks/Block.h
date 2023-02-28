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

struct BlockFace
{
public:
	enum Face { North, East, South, West, bot, top, unresolved };
	Face face = unresolved;

	Vector3 GetNormal()
	{
		switch (face)
		{
			case BlockFace::North:
				return Vector3(0, 0, -1);
				break;
			case BlockFace::East:
				return Vector3(1, 0, 0);
				break;
			case BlockFace::South:
				return Vector3(0, 0, 1);
				break;
			case BlockFace::West:
				return Vector3(-1, 0, 0);
				break;
			case BlockFace::bot:
				return Vector3(0, -1, 0);
				break;
			case BlockFace::top:
				return Vector3(0, 1, 0);
				break;
			case BlockFace::unresolved:
				return Vector3(0, 0, 0);
				break;
			default:
				return Vector3(0, 0, 0);
				break;
		}
	}

	static Vector3 GetNormal(Face _face)
	{
		switch (_face)
		{
		case BlockFace::North:
			return Vector3(0, 0, -1);
			break;
		case BlockFace::East:
			return Vector3(1, 0, 0);
			break;
		case BlockFace::South:
			return Vector3(0, 0, 1);
			break;
		case BlockFace::West:
			return Vector3(-1, 0, 0);
			break;
		case BlockFace::bot:
			return Vector3(0, -1, 0);
			break;
		case BlockFace::top:
			return Vector3(0, 1, 0);
			break;
		case BlockFace::unresolved:
			return Vector3(0, 0, 0);
			break;
		default:
			return Vector3(0, 0, 0);
			break;
		}
	}

	void operator=(BlockFace rh)
	{
		this->face = rh.face;
	}

	void operator=(Face rh)
	{
		this->face = rh;
	}

	bool operator==(BlockFace rh)
	{
		return this->face == rh.face;
	}

	bool operator==(Face rh)
	{
		return this->face == rh;
	}
};

struct BlockData
{
	Vector3 position;
	Block::BlockID blockId;
	float neighborIds[6];
};
