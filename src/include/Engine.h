#ifndef ENGINE_CLASS_H
#define ENGINE_CLASS_H

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "LayerStack.h"

#include "Window.h"
#include "Input.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

#define BIND_EVENT_FN(x) std::bind(&Engine::x, this, std::placeholders::_1)

class Engine
{
public:
	Engine();
	virtual ~Engine();

	void run();

	void onEvent(Event& e);

	void pushLayer(Layer* layer);
	void pushOverlay(Layer* overlay);

	Window& getWindow() { return *window; }

	static Engine& get() { return *staticInstance; }

private:
	bool onWindowClose(WindowCloseEvent& e);

	Window* window;
	LayerStack layerStack;

	bool isRunning = true;

	static Engine* staticInstance;
};

#endif // !ENGINE_CLASS_H
