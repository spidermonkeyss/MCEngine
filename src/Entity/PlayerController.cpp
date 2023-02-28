#include "PlayerController.h"
#include "Time/TimeHandler.h"
#include "Physics/RayCast.h"

void PlayerController::Update(ChunkHandler* chunkHandler)
{
    //Camera control
    playerEntity->transform.rotation.y -= mouseSpeed * TimeHandler::DeltaTime() * Input::GetMouseDeltaX();
    playerEntity->transform.rotation.x -= mouseSpeed * TimeHandler::DeltaTime() * Input::GetMouseDeltaY();

    //Movement control
    //if (Input::KeyPressed(KeyCode::w))
    //    playerEntity->transform.position = playerEntity->transform.position + playerEntity->transform.Forward() * moveSpeed * TimeHandler::DeltaTime();
    //if (Input::KeyPressed(KeyCode::s))                                  
    //    playerEntity->transform.position = playerEntity->transform.position - playerEntity->transform.Forward() * moveSpeed * TimeHandler::DeltaTime();
    //if (Input::KeyPressed(KeyCode::a))                                  
    //    playerEntity->transform.position = playerEntity->transform.position - playerEntity->transform.Right() * moveSpeed * TimeHandler::DeltaTime();
    //if (Input::KeyPressed(KeyCode::d))                                  
    //    playerEntity->transform.position = playerEntity->transform.position + playerEntity->transform.Right() * moveSpeed * TimeHandler::DeltaTime();

    playerEntity->velocity.SetVector(0, 0, 0);

    if (Input::KeyPressed(KeyCode::w))
        playerEntity->velocity = playerEntity->transform.Forward() * moveSpeed;
    if (Input::KeyPressed(KeyCode::s))
        playerEntity->velocity = playerEntity->transform.Forward() * -moveSpeed;
    if (Input::KeyPressed(KeyCode::a))
        playerEntity->velocity = playerEntity->transform.Right() * -moveSpeed;
    if (Input::KeyPressed(KeyCode::d))
        playerEntity->velocity = playerEntity->transform.Right() * moveSpeed;

    //Cast ray
    if (Input::KeyPressed(KeyCode::q))
    {
        //Ray ray = RayCast::Cast(Vector3(0, 65, 13), Vector3(0, 0, 1), 5, chunkHandler);
        Ray ray = RayCast::Cast(playerEntity->transform.position, playerEntity->transform.Forward(), 5, chunkHandler);
        if (ray.hit)
            std::cout << "Start:" << ray.rPos.ToString() << " Dir:" << ray.rDir.ToString() << " Length:" << ray.rLength << " Block:" << ray.block->position.ToString() << " Face:" << ray.blockFace.face << std::endl;
    }
}

void PlayerController::SetCamera(Camera* _camera)
{
    camera = _camera;
}
