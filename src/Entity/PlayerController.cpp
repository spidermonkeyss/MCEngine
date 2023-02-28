#include "PlayerController.h"
#include "Time/TimeHandler.h"
#include "Physics/Physics.h"

void PlayerController::Update(ChunkHandler* chunkHandler)
{
    //Camera control
    playerEntity->transform.rotation.y -= mouseSpeed * TimeHandler::DeltaTime() * Input::GetMouseDeltaX();
    playerEntity->transform.rotation.x -= mouseSpeed * TimeHandler::DeltaTime() * Input::GetMouseDeltaY();
   
    playerEntity->velocity.SetVector(0, 0, 0);

    Vector3 movementDir;

    if (Input::KeyHeld(KeyCode::w))
        movementDir = movementDir + playerEntity->transform.Forward();
    if (Input::KeyHeld(KeyCode::s))
        movementDir = movementDir - playerEntity->transform.Forward();
    if (Input::KeyHeld(KeyCode::a))
        movementDir = movementDir - playerEntity->transform.Right();
    if (Input::KeyHeld(KeyCode::d))
        movementDir = movementDir + playerEntity->transform.Right();

    playerEntity->velocity = movementDir.Normal() * moveSpeed;

    //Cast ray
    if (Input::KeyPressed(KeyCode::q))
    {
        Ray ray = Physics::CastRay(playerEntity->transform.position, playerEntity->transform.Forward(), 5, chunkHandler);
        if (ray.hit)
        { 
            //std::cout << "Start:" << ray.rPos.ToString() << " Dir:" << ray.rDir.ToString() << " Length:" << ray.rLength << " Chunk:" << ray.chunk->chunkPos.ToString() << " Block:" << ray.block->position.ToString() << " Face:" << ray.blockFace.face << std::endl;
            ray.chunk->RemoveBlock(ray.block->position);
        }
    }
}

void PlayerController::SetCamera(Camera* _camera)
{
    camera = _camera;
}
