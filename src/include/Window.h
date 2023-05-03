#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"



struct WindowProperties
{
	std::string title;
	unsigned int width;
	unsigned int height;

	WindowProperties(
		const std::string& title = "ENGINE",
		unsigned int height = 720,
		unsigned int width = 1280
	) : title(title), height(height), width(width) {}
};

class Window {
public:
	Window(const WindowProperties& props = WindowProperties());
	virtual ~Window();

	using EventCallbackFn = std::function<void(Event&)>;

	void onUpdate();

	inline unsigned int getWidth() const { return data.width; }
	inline unsigned int getHeight() const { return data.height; }

	inline void setEventCallback(const EventCallbackFn& callback) { data.eventCallback = callback; }
	void setVSync(bool enabled);
	bool isVSync() const { return data.VSync; }

	inline GLFWwindow* getGLFWWindow() const { return window; }

private:

	//static Window* create(const WindowProperties& props = WindowProperties());

	void init(const WindowProperties& props);
	void shutdown();

	GLFWwindow* window;

	struct WindowData
	{
		std::string Title;
		unsigned int width, height;
		bool VSync;

		EventCallbackFn eventCallback;
	};

	WindowData data;

};

#endif // !WINDOW_CLASS_H
