#include "Entity.h"

Entity::Entity()
	:transform(Transform()), originChunk(nullptr), velocity(Vector3())
{
}

Entity::~Entity()
{
}

void Entity::CheckOriginChunk(ChunkHandler* chunkHandler, List<Entity>* entityList)
{
	for (int i = 0; i < entityList->Size(); i++)
		entityList->At(i)->originChunk = chunkHandler->GetChunkFromWorldPosition(entityList->At(i)->transform.position);
}

void Entity::Gravity(List<Entity>* entityList)
{
	for (int i = 0; i < entityList->Size(); i++)
		entityList->At(i)->velocity.y -= 9.81f;
}
