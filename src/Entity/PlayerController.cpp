#include "PlayerController.h"
#include "Time/TimeHandler.h"
#include "Physics/Physics.h"

void PlayerController::CheckLookingAtBlock(ChunkHandler * chunkHandler)
{
    Ray ray = Physics::CastRay(playerEntity->transform.position, playerEntity->transform.Forward(), 5, chunkHandler);
    if (ray.hit)
    {
        //std::cout << " Length:" << ray.rLength << " Block:" << ray.block->position.ToString() << " Face:" << ray.blockFace.face << std::endl;
        isLookingAtBlock = true;
        Vector3 blockWorldPos = ray.chunk->blocks[ray.chunk->GetBlockIndex(ray.block->position.x, ray.block->position.y, ray.block->position.z)].position;
        blockLookingAtPos.SetVector(blockWorldPos.x, blockWorldPos.y, blockWorldPos.z);
        chunkLookingAt = ray.chunk;
        blockFaceLookingAt = ray.blockFace;
    }
    else
    {
        isLookingAtBlock = false;
        blockLookingAtPos.SetVector(-1, -1, -1);
        chunkLookingAt = nullptr;
        blockFaceLookingAt = BlockFace::unresolved;
    }
}

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

    CheckLookingAtBlock(chunkHandler);

    if (Input::KeyPressed(KeyCode::mouse1) && isLookingAtBlock)
    {
        chunkLookingAt->RemoveBlock(blockLookingAtPos);
    }

    if (Input::KeyPressed(KeyCode::mouse2) && isLookingAtBlock)
    {
        chunkLookingAt->ChangeBlock(blockLookingAtPos + blockFaceLookingAt.GetNormal(), Block::Cobblestone);
    }

}

void PlayerController::SetCamera(Camera* _camera)
{
    camera = _camera;
}
