#include "Engine.h"

// Temporary window sizes
#define WINDOW_WIDTH_PX 1280
#define WINDOW_HEIGHT_PX 720

int main()
{
	std::cout << "HELLO PROJECT CERES" << std::endl;

	Engine ceresEngine;

	const char* windowName = "Project Ceres";
	ceresEngine.createWindow(1280, 720, windowName, false);

	ceresEngine.displayWindow();

	return 0;
}