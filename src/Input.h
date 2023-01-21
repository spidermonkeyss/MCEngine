#pragma once
#pragma once
#include "Renderer/GLCall.h"
#include "Math/Vector2.h"

static enum KeyCode { w, a, s, d, q, e, z, x };

static class Input
{
private:
    static int windowWidth, windowHeight;
    static double prevMousePosX, prevMousePosY;
    static double mousePosX, mousePosY;
    static double mousePosDeltaX, mousePosDeltaY;
public:
    static GLFWwindow* window;

    static bool lockCursor;

    static bool KeyPressed(KeyCode keyCode);
    static bool KeyReleased(KeyCode keyCode);

    static double GetMouseDeltaX();
    static double GetMouseDeltaY();

    static void Update();
};

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        Input::lockCursor = false;
        //glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    
}