#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int Texture::debug_texture_count = 0;

void Texture::Create2DTexture()
{
	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);
}

void Texture::CreateCubeMapTexture()
{
	int cellWidth = (m_Width / 4);
	int cellHeight = (m_Height / 3);

	if (m_LocalBuffer)
	{
		m_LocalCubeMapBuffer.resize(12);
		int size = cellWidth * cellHeight * m_BPP;
		for (int i = 0; i < 12; i++)
			m_LocalCubeMapBuffer.at(i) = new unsigned char[size];

		//std::cout << "Pixel Width:" << m_Width << " Pixel Height:" << m_Height << std::endl;
		for (int y = 0; y < m_Height; y++)
		{
			for (int x = 0; x < m_Width; x++)
			{
				int cellIndex = floorf((float)y / cellHeight) * 4.0f + floorf((float)x / cellWidth);
				if (cellIndex == 1 || cellIndex == 4 || cellIndex == 5 || cellIndex == 6 || cellIndex == 7 || cellIndex == 9)
				{
					int textureIndex = (y * m_Width + x) * m_BPP;

					int cellX = x % cellWidth;
					int cellY = y % cellHeight;
					int cellStride = cellWidth;
					int innerCellIndex = (cellY * cellStride + cellX) * m_BPP;

					for (int i = 0; i < m_BPP; i++)
						m_LocalCubeMapBuffer.at(cellIndex)[innerCellIndex + i] = m_LocalBuffer[textureIndex + i];

					//if (cellIndex == 5)
					//{
					//	std::cout << "cellIndex:" << cellIndex << " InnerCellIndex:" << innerCellIndex << " textureIndex:" << textureIndex << " pixelX:" << x << " pixelY:" << y << " cellX:" << cellX << " cellY:" << cellY << std::endl;
					//}
				}
			}
		}

		GLCall(glGenTextures(1, &m_RendererID));
		GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID));

		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, cellWidth, cellHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalCubeMapBuffer.at(6)));
		GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, cellWidth, cellHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalCubeMapBuffer.at(4)));
		GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, cellWidth, cellHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalCubeMapBuffer.at(1)));
		GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, cellWidth, cellHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalCubeMapBuffer.at(9)));
		GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, cellWidth, cellHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalCubeMapBuffer.at(5)));
		GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, cellWidth, cellHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalCubeMapBuffer.at(7)));

		GLCall(glGenerateMipmap(GL_TEXTURE_CUBE_MAP));
		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));

		GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));

		if (m_LocalBuffer)
			stbi_image_free(m_LocalBuffer);

		for (int i = 0; i < 12; i++)
		{
			if (m_LocalCubeMapBuffer.at(i))
				free(m_LocalCubeMapBuffer.at(i));
		}
	}
}

Texture::Texture()
	: m_RendererID(0), m_FilePath(""), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0), textureType(0)
{
	std::cout << "Texture created id:" << m_RendererID << std::endl;
	debug_texture_count++;
}

Texture::Texture(const std::string& filePath, int textureType)
	: m_RendererID(0), m_FilePath(filePath), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0), textureType(textureType)
{
	//2D Texture
	if (textureType == 0)
	{
		stbi_set_flip_vertically_on_load(1);
		m_LocalBuffer = stbi_load(filePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);
		Create2DTexture();
	}
	//Cube Map
	else if (textureType == 1)
	{
		//Cube map draws texture starting from top left instead of bottom left
		stbi_set_flip_vertically_on_load(0);
		m_LocalBuffer = stbi_load(filePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);
		CreateCubeMapTexture();
	}

	std::cout << "Texture created id:" << m_RendererID << std::endl;
	debug_texture_count++;
}

Texture::~Texture()
{
	std::cout << "Texture deleted id:" << m_RendererID << std::endl;
	GLCall(glDeleteTextures(1, &m_RendererID));
	debug_texture_count--;
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));

	if (textureType == 0)
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
	}
	else if (textureType == 1)
	{
		GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID));
	}
}

void Texture::Unbine() const
{
	if (textureType == 0)
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}
	else if (textureType == 1)
	{
		GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
	}
}

void Texture::CreateTexture(unsigned char* buffer, int width, int height, int bpp)
{
	//if (m_RendererID != 0)
	//{
	//	std::cout << "Texture deleted id:" << m_RendererID << std::endl;
	//	GLCall(glDeleteTextures(1, &m_RendererID));
	//	m_RendererID = 0;
	//	debug_texture_count--;
	//}

	textureType = 0;
	m_LocalBuffer = buffer;
	m_Width = width;
	m_Height = height;
	m_BPP = bpp;
	Create2DTexture();
}

unsigned char* Texture::GetTexture(const std::string& filePath, int* width, int* height, int* bpp)
{
	stbi_set_flip_vertically_on_load(1);
	return stbi_load(filePath.c_str(), width, height, bpp, 4);
}