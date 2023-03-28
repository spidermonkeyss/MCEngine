#pragma once
#include "GLCall.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Camera.h"
#include "Entity/PlayerController.h"
#include "Chunk/ChunkHandler.h"
#include "UI/UI.h"

class Renderer
{
private:
	void DrawUI(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void DrawChunks(const VertexArray& va, unsigned int count, const Shader& shader) const;
public:
	Renderer();
	~Renderer();

	void Render(Camera* camera, ChunkHandler* chunkHandler, PlayerController* playerController, UI* ui);
	void Clear() const;
};