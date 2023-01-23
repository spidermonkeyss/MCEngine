#include "PlayerController.h"
#include "Time/TimeHandler.h"

void PlayerController::Update()
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


    //std::cout << camera.transform.position.ToString() << std::endl;
}

void PlayerController::SetCamera(Camera* _camera)
{
    camera = _camera;
}
