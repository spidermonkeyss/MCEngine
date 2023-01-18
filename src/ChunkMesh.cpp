#include "ChunkMesh.h"
#include "Chunk.h"
#include "Vector3.h"

/*
const float ChunkMesh::vertexCount = 8;
const float ChunkMesh::vertexSize = 6;
const float ChunkMesh::indexCount = 36;

const float ChunkMesh::base_cubeMap_vertices[48] =
{
    -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,//bot front left
     0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,//bot front right
     0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,//top front right
    -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f,//top front left

     0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,//bot back left
    -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f,//bot back right
    -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,//top back right
     0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f //top back left
};

const unsigned int ChunkMesh::base_indices[36] =
{
    0, 1, 2,
    2, 3, 0,
    4, 5, 6,
    6, 7, 4,
    5, 0, 3,
    3, 6, 5,
    1, 4, 7,
    7, 2, 1,
    3, 2, 7,
    7, 6, 3,
    5, 4, 1,
    1, 0, 5
};

void ChunkMesh::GenerateMeshOld()
{
    std::cout << "ChunkMeshGen" << std::endl;

    std::vector<float> verticesVec;
    std::vector<unsigned int> indicesVec;
    verticesVec.resize(vertexCount * vertexSize * Chunk::chunkSize);
    indicesVec.resize(indexCount * Chunk::chunkSize);

    int x = 0;
    int y = 0;
    int z = 0;
    for (int blockIndex = 0; blockIndex < Chunk::chunkSize; blockIndex++)
    {
        for (int k = 0; k < vertexCount * vertexSize; k++)
        {
            verticesVec.at(blockIndex * vertexCount * vertexSize + k) = base_cubeMap_vertices[k];
        }
        for (int k = 0; k < vertexCount; k++)
        {
            verticesVec.at(blockIndex * vertexCount * vertexSize + k * vertexSize + 0) = base_cubeMap_vertices[k * (int)vertexSize + 0] + x;
            verticesVec.at(blockIndex * vertexCount * vertexSize + k * vertexSize + 1) = base_cubeMap_vertices[k * (int)vertexSize + 1] + y;
            verticesVec.at(blockIndex * vertexCount * vertexSize + k * vertexSize + 2) = base_cubeMap_vertices[k * (int)vertexSize + 2] - z;
        }
       
        for (int k = 0; k < indexCount; k++)
        {
            indicesVec.at(blockIndex * indexCount + k) = base_indices[k] + blockIndex * 8;
        }

        x++;
        if (x == Chunk::chunkWidth)
        {
            z++;
            x = 0;
        }
        if (z == Chunk::chunkWidth)
        {
            y++;
            z = 0;
        }
    }

    float* verticies = new float[verticesVec.size()];
    for (int i = 0; i < verticesVec.size(); i++)
        verticies[i] = verticesVec[i];

    unsigned int* indices = new unsigned int[indicesVec.size()];
    for (int i = 0; i < indicesVec.size(); i++)
        indices[i] = indicesVec[i];

    vertexBuffer.GenBuffer(verticies, verticesVec.size() * sizeof(float));
    layout.Push<float>(3);//positions attribute
    layout.Push<float>(3);//texture coords
    vertexArray.AddBuffer(vertexBuffer, layout);
    indexBuffer.BufferData(indices, indicesVec.size());

    delete[] verticies;
    delete[] indices;
}
*/

void ChunkMesh::GenerateMeshLayout()
{
    layout.Push<float>(3);//positions attribute
    layout.Push<unsigned int>(1);//id attribute
    layout.Push<float>(3);//first 3 neighbor id attribute
    layout.Push<float>(3);//second 3 neighbor id attribute
}

ChunkMesh::ChunkMesh()
{
    GenerateMeshLayout();
}

ChunkMesh::~ChunkMesh()
{
}

void ChunkMesh::UpdateMesh(BlockData* blocks)
{
    vertexBuffer.GenBuffer(blocks, Chunk::chunkSize * sizeof(BlockData));
    vertexArray.AddBuffer(vertexBuffer, layout);
}