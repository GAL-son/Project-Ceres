#include "Engine.h"

int Engine::createWindow(int wWidth, int wHeight, const char* wTitle, bool wFullScreen)
{
	// Initialize glfw and make sure that initialization is successfull
	if (!glfwInit())
	{
		std::cout << "FAILED TO INITIALIZE GLFW" << std::endl;
		return -1;
	}

	// Hint glfw version of OpenG (3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Hint glfw what profile of OpenGL is used
	// Core - no deprecated functions are used
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window with given parameters
	appWindow = glfwCreateWindow
	(
		wWidth,
		wHeight,
		wTitle,
		// If window is fullscreen get primary monitor
		(wFullScreen) ? glfwGetPrimaryMonitor() : nullptr,
		nullptr
	);

	// Check if window creation was succesfull
	if (appWindow == nullptr)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	windowWidth = wWidth;
	windowHeight = wHeight;

	glfwMakeContextCurrent(appWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	return 0;
}

void Engine::displayWindow()
{
	glViewport(0, 0, windowWidth, windowHeight);

	while (!glfwWindowShouldClose(appWindow))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(appWindow);
		glfwPollEvents();
	}

	glfwTerminate();
}