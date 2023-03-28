#pragma once
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Blocks/BlockRegister.h"

class UI
{
private:
	VertexBuffer vertexBuffer;
	VertexArray vertexArray;
	VertexBufferLayout layout;
	IndexBuffer indexBuffer;

	glm::mat4 proj;

	std::string shaderFilePath = "res/Shaders/UIShader.shader";
	std::string textureFilePath = "res/Textures/pike.png";
public:
	UI();

	std::unique_ptr<Shader> uiShader;
	std::unique_ptr<Texture> uiTexture;

	inline VertexArray* GetVertexArray() { return &vertexArray; }
	inline IndexBuffer* GetIndexBuffer() { return &indexBuffer; }
	inline glm::mat4* GetProjMat() { return &proj; }
};