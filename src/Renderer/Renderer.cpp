#include "Renderer.h"
#include "Blocks/Block.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Render(Camera* camera, ChunkHandler* chunkHandler, PlayerController* playerController, UI* ui)
{
	glm::mat4 v = glm::inverse(playerController->playerEntity->transform.GetTransformMatrix());
	Block::blockShader->Bind();
	Block::blockTextureAtlas->Bind(0);
	//Block::blockShader->SetUniform1i("u_TextureAtlas", 0);
	
	for (int i = 0; i < chunkHandler->chunkBufferSize; i++)
	{
		if (chunkHandler->chunks[i].isLoaded)
		{
			Block::blockShader->SetUniformMat4f("u_M", chunkHandler->chunks[i].chunkMatrix4x4);
			Block::blockShader->SetUniformMat4f("u_V", v);
			Block::blockShader->SetUniformMat4f("u_P", *camera->GetProjMat());
		
			DrawChunks(*chunkHandler->chunks[i].chunkMesh.GetVertexArray(), Chunk::chunkSize, *Block::blockShader);
		}
	}

	ui->uiShader->Bind();
	ui->uiTexture->Bind();
	ui->uiShader->SetUniformMat4f("u_proj", *ui->GetProjMat());
	DrawUI(*ui->GetVertexArray(), *ui->GetIndexBuffer(), *ui->uiShader);
}

void Renderer::DrawUI(const VertexArray & va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), ib.GetDataType(), nullptr));
}

void Renderer::DrawChunks(const VertexArray& va, unsigned int count, const Shader& shader) const
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