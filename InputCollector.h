#pragma once
#include <GLFW/glfw3.h>

class InputCollector
{
private:
public:
	static bool pressedKeys[2000];
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		if (key < 2000)
		{
			if (action == GLFW_PRESS)
			{
				InputCollector::pressedKeys[key] = GL_TRUE;
			}
			if (action == GLFW_RELEASE)
			{
				InputCollector::pressedKeys[key] = GL_FALSE;
			}
		}
	}

	static bool isPressed(int key)
	{
		return InputCollector::pressedKeys[key];
	}
	InputCollector();
	~InputCollector();
};

