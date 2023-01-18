#pragma once
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "BlockRegister.h"

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