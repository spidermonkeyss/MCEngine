#include "FunctionTimer.h"
#include "GLCall.h"

FunctionTimer::FunctionTimer()
{
    startTime = glfwGetTime();
    endTime = 0;
    totalTime = 0;
}

FunctionTimer::~FunctionTimer()
{
    endTime = glfwGetTime();
    totalTime = endTime - startTime;
    std::cout << totalTime * 1000 << std::endl;
}
