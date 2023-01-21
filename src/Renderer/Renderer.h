#pragma once
#include "GLCall.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Camera.h"
#include "Entity/PlayerController.h"
#include "Chunk/ChunkHandler.h"

#include "glm/glm.hpp"

class Renderer
{
private:
	glm::mat4 m;
	glm::mat4 v;
	glm::mat4 vp;
	glm::mat4 mvp;

	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void Draw(const VertexArray& va, unsigned int count, const Shader& shader) const;
public:
	Renderer();
	~Renderer();

	void Render(Camera* camera, ChunkHandler* chunkHandler, PlayerController* playerController);
	void Clear() const;
};