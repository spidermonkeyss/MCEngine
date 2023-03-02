#include "Input.h"

GLFWwindow* Input::window;
std::vector<KeyState> Input::keyStates;
int Input::windowWidth, Input::windowHeight;
double Input::prevMousePosX, Input::prevMousePosY;
double Input::mousePosX, Input::mousePosY;
double Input::mousePosDeltaX, Input::mousePosDeltaY;
bool Input::lockCursor = true;

bool Input::KeyPressed(KeyCode keyCode)
{
    return (keyStates.at(keyCode) == Pressed);
}

bool Input::KeyHeld(KeyCode keyCode)
{
    return (keyStates.at(keyCode) == Held);
}

bool Input::KeyReleased(KeyCode keyCode)
{
    return (keyStates.at(keyCode) == Released);
}

double Input::GetMouseDeltaX()
{
    return mousePosDeltaX;
}

double Input::GetMouseDeltaY()
{
    return mousePosDeltaY;
}

void Input::MouseUpdate()
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

void Input::Init()
{
    for (int i = 0; i < KeyCode::SIZE; i++)
    {
        keyStates.push_back(KeyState::None);
    }
}

void Input::UpdatePressToHeld()
{
    for (int i = 0; i < KeyCode::SIZE; i++)
    {
        if (keyStates.at(i) == Pressed)
            keyStates.at(i) = Held;
    }
}

void Input::ResetReleaseKeyStates()
{
    for (int i = 0; i < KeyCode::SIZE; i++)
    {
        if (keyStates.at(i) == Released)
            keyStates.at(i) = None;
    }
}

void Input::KeyCallBack(int key, int action)
{
    KeyCode keyCode;
    switch (key)
    {
    case GLFW_KEY_W:
        keyCode = w;
        break;
    case GLFW_KEY_A:
        keyCode = a;
        break;
    case GLFW_KEY_S:
        keyCode = s;
        break;
    case GLFW_KEY_D:
        keyCode = d;
        break;
    case GLFW_KEY_Q:
        keyCode = q;
        break;
    case GLFW_KEY_E:
        keyCode = e;
        break;
    case GLFW_KEY_Z:
        keyCode = z;
        break;
    case GLFW_KEY_X:
        keyCode = x;
        break;
    default:
        return;
        break;
    }

    if (action == GLFW_PRESS)
    {
        if (keyStates.at(keyCode) == None)
            keyStates.at(keyCode) = Pressed;
    }
    else if (action == GLFW_RELEASE)
    {
        keyStates.at(keyCode) = Released;
    }
}

void Input::MouseCallBack(int button, int action)
{
    KeyCode keyCode;
    switch (button)
    {
    case GLFW_MOUSE_BUTTON_1:
        keyCode = mouse1;
        break;
    case GLFW_MOUSE_BUTTON_2:
        keyCode = mouse2;
        break;
    }

    if (action == GLFW_PRESS)
    {
        if (keyStates.at(keyCode) == None)
            keyStates.at(keyCode) = Pressed;
    }
    else if (action == GLFW_RELEASE)
    {
        keyStates.at(keyCode) = Released;
    }
}
