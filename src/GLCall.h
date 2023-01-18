#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#ifdef _DEBUG
#define ASSERT(x) if (!(x)) __debugbreak();
//Clear error runs first, then the function, then gllogcall
#define GLCall(x) GLClearError();\
		x;\
		ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
#define GLCall(x) x
#define ASSERT(x) x
#endif

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << ")" << function <<
			" " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}