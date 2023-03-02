#pragma once
#pragma once
#include "Renderer/GLCall.h"
#include "Math/Vector2.h"
#include <vector>

static enum KeyCode { w, a, s, d, q, e, z, x, mouse1, mouse2, SIZE };
static enum KeyState { Pressed, Held, Released, None};

static class Input
{
private:
    static std::vector<KeyState> keyStates;
    static int windowWidth, windowHeight;
    static double prevMousePosX, prevMousePosY;
    static double mousePosX, mousePosY;
    static double mousePosDeltaX, mousePosDeltaY;
public:
    static GLFWwindow* window;

    static bool lockCursor;

    static bool KeyPressed(KeyCode keyCode);
    static bool KeyHeld(KeyCode keyCode);
    static bool KeyReleased(KeyCode keyCode);

    static double GetMouseDeltaX();
    static double GetMouseDeltaY();

    static void Init();
    static void UpdatePressToHeld();
    static void ResetReleaseKeyStates();
    static void MouseUpdate();
    static void KeyCallBack(int key, int action);
    static void MouseCallBack(int button, int action);
};

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        Input::lockCursor = false;
   
    Input::KeyCallBack(key, action);

    //glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    Input::MouseCallBack(button, action);
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    
}