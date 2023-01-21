#pragma once
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Blocks/BlockRegister.h"

class ChunkMesh
{
private:
	VertexBuffer vertexBuffer;
	VertexArray vertexArray;
	VertexBufferLayout layout;

	void GenerateMeshLayout();
public:
	ChunkMesh();
	~ChunkMesh();

	void UpdateMesh(BlockData* blocks);

	inline VertexArray* GetVertexArray() { return &vertexArray; }
};