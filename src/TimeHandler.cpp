#include "TimeHandler.h"
#include "GLCall.h"

double TimeHandler::startTime;
double TimeHandler::currentTime;
double TimeHandler::gameTime;
double TimeHandler::deltaTime;

void TimeHandler::Init()
{
    startTime = glfwGetTime();
    currentTime = glfwGetTime();
    gameTime = 0;
    deltaTime = 0;
}

void TimeHandler::UpdateTime()
{
    deltaTime = glfwGetTime() - currentTime;
    currentTime = glfwGetTime();
    gameTime = currentTime - startTime;
}
