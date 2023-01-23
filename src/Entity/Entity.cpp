#include "Entity.h"
#include "Time/TimeHandler.h"

const int Entity::MAX_ENTITIES = 16;

Entity::Entity()
	:transform(Transform()), originChunk(nullptr), velocity(Vector3())
{
}

Entity::~Entity()
{
}

void Entity::CheckOriginChunk(ChunkHandler* chunkHandler, Entity* entityList)
{
	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		if (entityList[i].isLoaded)
			entityList[i].originChunk = chunkHandler->GetChunkFromWorldPosition(entityList[i].transform.position);
	}
}

void Entity::UpdatePositions(Entity* entityList)
{
	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		if (entityList[i].isLoaded)
			entityList[i].transform.position = entityList[i].transform.position + entityList[i].velocity * TimeHandler::DeltaTime();
	}
}
