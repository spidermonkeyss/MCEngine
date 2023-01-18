#include "Input.h"

GLFWwindow* Input::window;
int Input::windowWidth, Input::windowHeight;
double Input::prevMousePosX, Input::prevMousePosY;
double Input::mousePosX, Input::mousePosY;
double Input::mousePosDeltaX, Input::mousePosDeltaY;
bool Input::lockCursor = true;

bool Input::KeyPressed(KeyCode keyCode)
{
    switch (keyCode)
    {
    case w:
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            return true;
        break;
    case a:
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            return true;
        break;
    case s:
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            return true;
        break;
    case d:
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            return true;
        break;
    case q:
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            return true;
        break;
    case e:
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            return true;
        break;
    case z:
        if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
            return true;
        break;
    case x:
        if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
            return true;
        break;
    default:
        break;
    }
    return false;
}

bool Input::KeyReleased(KeyCode keyCode)
{
    switch (keyCode)
    {
    case w:
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)
            return true;
        break;
    case a:
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE)
            return true;
        break;
    case s:
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE)
            return true;
        break;
    case d:
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE)
            return true;
        break;
    case q:
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_RELEASE)
            return true;
        break;
    case e:
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE)
            return true;
        break;
    case z:
        if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_RELEASE)
            return true;
        break;
    case x:
        if (glfwGetKey(window, GLFW_KEY_X) == GLFW_RELEASE)
            return true;
        break;
    default:
        break;
    }
    return false;
}

double Input::GetMouseDeltaX()
{
    return mousePosDeltaX;
}

double Input::GetMouseDeltaY()
{
    return mousePosDeltaY;
}

void Input::Update()
{
    if (lockCursor)
    {
        glfwGetCursorPos(window, &mousePosX, &mousePosY);
        mousePosDeltaX = mousePosX - prevMousePosX;
        mousePosDeltaY = mousePosY - prevMousePosY;

        glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
        prevMousePosX = (double)windowWidth / 2;
        prevMousePosY = (double)windowHeight / 2;
        glfwSetCursorPos(window, prevMousePosX, prevMousePosY);
    }
    //else
    //{
    //    prevMousePosX = mousePosX;
    //    prevMousePosY = mousePosY;
    //}
}
