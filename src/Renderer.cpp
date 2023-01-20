#include "Renderer.h"
#include "Blocks/Block.h"

#include "glm/gtc/matrix_transform.hpp"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Render(Camera* camera, ChunkHandler* chunkHandler)
{
	v = glm::inverse(camera->transform.GetTransformMatrix());
	vp = *camera->GetProjMat() * v;

	for (int i = 0; i < chunkHandler->chunkBufferSize; i++)
	{
		if (chunkHandler->chunks[i].isLoaded)
		{
			m = glm::translate(glm::mat4(1.0f), glm::vec3(chunkHandler->chunks[i].chunkPos.x * Chunk::chunkWidth, 0, chunkHandler->chunks[i].chunkPos.y * Chunk::chunkWidth));
			mvp = vp * m;
		
			Block::blockShader->Bind();
			Block::blockShader->SetUniformMat4f("u_MVP", mvp);
		
			Draw(*chunkHandler->chunks[i].chunkMesh.GetVertexArray(), Chunk::chunkSize, *Block::blockShader);
		}
	}
}

void Renderer::Draw(const VertexArray & va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), ib.GetDataType(), nullptr));
}

void Renderer::Draw(const VertexArray& va, unsigned int count, const Shader& shader) const
{
	shader.Bind();
	va.Bind();
	GLCall(glDrawArrays(GL_POINTS, 0, count));
}

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GLCall(glClearColor(0.14f, 0.5f, 0.85f, 1.0f));
	// 0.14f, 0.5f, 0.85f, 1.0f
}