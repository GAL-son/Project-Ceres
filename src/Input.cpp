#include "include/Input.h"

//#include <GLFW/glfw3.h>
#include "include/Engine.h"

bool Input::isKeyPressed(int keyCode)
{
	GLFWwindow* window = Engine::get().getWindow().getGLFWWindow();
	auto state = glfwGetKey(window, keyCode);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::isMouseButtonPressed(int button)
{
	GLFWwindow* window = Engine::get().getWindow().getGLFWWindow();
	auto state = glfwGetMouseButton(window, button);
	return state == GLFW_PRESS;

}

float Input::getMouseX()
{
	GLFWwindow* window = Engine::get().getWindow().getGLFWWindow();
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	return (float)x;
}

float Input::getMouseY()
{
	GLFWwindow* window = Engine::get().getWindow().getGLFWWindow();
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	return (float)y;
}