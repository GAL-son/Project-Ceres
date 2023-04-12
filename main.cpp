#include "Engine.h"

int main()
{
	std::cout << "HELLO PROJECT CERES" << std::endl;

	Engine ceresEngine = Engine();

	const char* windowName = "Project Ceres";
	ceresEngine.createWindow(1280, 720, windowName, false);

	ceresEngine.displayWindow();

	return 0;
}