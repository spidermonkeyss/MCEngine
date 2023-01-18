#pragma once
#include "GLCall.h"
#include <vector>

class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	std::vector<unsigned char*> m_LocalCubeMapBuffer;
	int m_Width, m_Height, m_BPP;
	unsigned int textureType;

	void Create2DTexture();
	void CreateCubeMapTexture();
public:
	Texture();
	Texture(const std::string& filePath, int textureType);
	~Texture();

	static int debug_texture_count;

	void Bind(unsigned int slot = 0) const;
	void Unbine() const;

	void CreateTexture(unsigned char* buffer, int width, int height, int bpp);
	
	static unsigned char* GetTexture(const std::string& filePath, int* width, int* height, int* bpp);

	inline int GetRenderID() const { return m_RendererID; }
	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	inline std::string GetFilePath() const { return m_FilePath; }
};