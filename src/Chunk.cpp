#include "Chunk.h"

int Chunk::chunkSize = Chunk::chunkWidth * Chunk::chunkWidth * Chunk::chunkHeight;
unsigned int Chunk::chunkIdCount = 0;

void Chunk::GenerateBlocks()
{
    int blockIndex = 0;
    for (int y = 0; y < chunkHeight; y++)
    {
        for (int z = 0; z < chunkWidth; z++)
        {
            for (int x = 0; x < chunkWidth; x++)
            {
                blockIndex = GetBlockIndex(x, y, z);
                BlockData* block = &blocks[blockIndex];
                block->position.SetVector(x, y, z);
                if (y <= 60)
                    block->blockId = Block::BlockID::Cobblestone;
                else if (y <= 64)
                    block->blockId = Block::BlockID::Grass;
                else if (y <= 68)
                {
                    if ((x == 0 || x == Chunk::chunkWidth-1) && (z == 0 || z == Chunk::chunkWidth-1))
                        block->blockId = Block::BlockID::Wood;
                    else
                        block->blockId = Block::BlockID::Air;
                }
                else
                    block->blockId = Block::BlockID::Air;
            }
        }
    }
}

void Chunk::NeighborBlockIdUpdate(int i)
{
    x = blocks[i].position.x;
    y = blocks[i].position.y;
    z = blocks[i].position.z;

    north = GetBlockIndex(x, y, z - 1);
    east = GetBlockIndex(x + 1, y, z);
    south = GetBlockIndex(x, y, z + 1);
    west = GetBlockIndex(x - 1, y, z);
    bot = GetBlockIndex(x, y - 1, z);
    top = GetBlockIndex(x, y + 1, z);

    //North
    if (north != -1)
        blocks[i].neighborIds[0] = blocks[north].blockId;
    else if (neighborChunks[0] != nullptr)
        blocks[i].neighborIds[0] = neighborChunks[0]->blocks[GetBlockIndexInNeighborChunk(x, y, z - 1)].blockId;
    else
        blocks[i].neighborIds[0] = -1;

    //East
    if (east != -1)
        blocks[i].neighborIds[1] = blocks[east].blockId;
    else if (neighborChunks[1] != nullptr)
        blocks[i].neighborIds[1] = neighborChunks[1]->blocks[GetBlockIndexInNeighborChunk(x + 1, y, z)].blockId;
    else
        blocks[i].neighborIds[1] = -1;

    //South
    if (south != -1)
        blocks[i].neighborIds[2] = blocks[south].blockId;
    else if (neighborChunks[2] != nullptr)
        blocks[i].neighborIds[2] = neighborChunks[2]->blocks[GetBlockIndexInNeighborChunk(x, y, z + 1)].blockId;
    else
        blocks[i].neighborIds[2] = -1;

    //West
    if (west != -1)
        blocks[i].neighborIds[3] = blocks[west].blockId;
    else if (neighborChunks[3] != nullptr)
        blocks[i].neighborIds[3] = neighborChunks[3]->blocks[GetBlockIndexInNeighborChunk(x - 1, y, z)].blockId;
    else
        blocks[i].neighborIds[3] = -1;

    //Bot
    if (bot != -1)
        blocks[i].neighborIds[4] = blocks[bot].blockId;
    else
        blocks[i].neighborIds[4] = -1;

    //Top
    if (top != -1)
        blocks[i].neighborIds[5] = blocks[top].blockId;
    else
        blocks[i].neighborIds[5] = Block::BlockID::Air;
}

void Chunk::UpdateNeighborBlockIds(bool allBlocks)
{
    for (int i = 0; i < chunkSize; i++)
    {
        if (allBlocks)
        {
            NeighborBlockIdUpdate(i);
            updateAllBlocks = false;
        }
        else
        {
            if (isBorderBlocks[i])
                NeighborBlockIdUpdate(i);
        }
    }
}

Chunk::Chunk()
    :chunkPos(Vector2()), isLoaded(false), isMarkedForUnload(false), isMarkedForUpdate(false), updateAllBlocks(false), neighborChunks(), x(0), y(0), z(0), north(0), east(0), south(0), west(0), bot(0), top(0)
{
    id = chunkIdCount++;
    blocks = new BlockData[chunkSize];
    isBorderBlocks = new bool[chunkSize];

    int i = 0;
    for (int y = 0; y < chunkHeight; y++)
    {
        for (int z = 0; z < chunkWidth; z++)
        {
            for (int x = 0; x < chunkWidth; x++)
            {
                //North
                if (z == 0)
                    isBorderBlocks[i] = true;
                //East
                else if (x == 0)
                    isBorderBlocks[i] = true;
                //South
                else if (z == chunkWidth - 1)
                    isBorderBlocks[i] = true;
                //West
                else if (x == chunkWidth - 1)
                    isBorderBlocks[i] = true;
                else
                    isBorderBlocks[i] = false;
                i++;
            }
        }
    }
}

Chunk::~Chunk() 
{
    delete[] blocks;
    delete[] isBorderBlocks;
}

void Chunk::Empty()
{
    isLoaded = false;
    chunkPos.x = 0;
    chunkPos.y = 0;
    isMarkedForUnload = false;
    isMarkedForUpdate = false;
    updateAllBlocks = false;
    neighborChunks[0] = nullptr;
    neighborChunks[1] = nullptr;
    neighborChunks[2] = nullptr;
    neighborChunks[3] = nullptr;
}

int Chunk::GetBlockIndex(float x, float y, float z)
{
    if (x < 0 || y < 0 || z < 0 || x >= chunkWidth || y >= chunkHeight || z >= chunkWidth)
        return -1;
    int index = y * (chunkWidth * chunkWidth) + z * chunkWidth + x;
    return index;
}

int Chunk::GetBlockIndexInNeighborChunk(float x, float y, float z)
{
    if (y < 0 || y >= chunkHeight)
        return -1;

    //North
    if (z < 0)
        z = chunkWidth + z;
    //East
    if (x >= chunkWidth)
        x = chunkWidth - x;
    //South
    if (z >= chunkWidth)
        z = chunkWidth - z;
    //West
    if (x < 0)
        x = chunkWidth + x;

    int index = y * (chunkWidth * chunkWidth) + z * chunkWidth + x;
    return index;
}