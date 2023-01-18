#include "PlayerController.h"
#include "TimeHandler.h"

void PlayerController::Update()
{
    //Camera control
    camera->transform.rotation.y -= mouseSpeed * TimeHandler::DeltaTime() * Input::GetMouseDeltaX();
    camera->transform.rotation.x -= mouseSpeed * TimeHandler::DeltaTime() * Input::GetMouseDeltaY();

    //Movement control
    if (Input::KeyPressed(KeyCode::w))
        camera->transform.position = camera->transform.position + camera->transform.Forward() * moveSpeed * TimeHandler::DeltaTime();
    if (Input::KeyPressed(KeyCode::s))                                  
        camera->transform.position = camera->transform.position - camera->transform.Forward() * moveSpeed * TimeHandler::DeltaTime();
    if (Input::KeyPressed(KeyCode::a))                                  
        camera->transform.position = camera->transform.position - camera->transform.Right() * moveSpeed * TimeHandler::DeltaTime();
    if (Input::KeyPressed(KeyCode::d))                                  
        camera->transform.position = camera->transform.position + camera->transform.Right() * moveSpeed * TimeHandler::DeltaTime();
    //std::cout << camera.transform.position.ToString() << std::endl;
}

void PlayerController::SetCamera(Camera* _camera)
{
    camera = _camera;
}
