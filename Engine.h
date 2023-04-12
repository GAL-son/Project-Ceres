#pragma once
#ifndef ENGINE_CLASS_H
#define ENGINE_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Sequence.h"

class Engine
{
	public:
		int createWindow(int wWidth, int wHeight, const char* wTitle, bool wFullScreen);
		void displayWindow();

	private:
		int windowWidth;
		int windowHeight;
		GLFWwindow* appWindow;
};


#endif // !ENGINE_CLASS_H
