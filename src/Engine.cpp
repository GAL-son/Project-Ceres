#include "include/Engine.h"
#include "include/Input.h"

//#define GLFW_INCLUDE_NONE



Engine* Engine::staticInstance = nullptr;

Engine::Engine()
{
	window = new Window();
	window->setEventCallback(BIND_EVENT_FN(onEvent));

	if (Engine::staticInstance == nullptr)
		staticInstance = this;
}

Engine::~Engine()
{
	delete window;
}

void Engine::run()
{

	
	// Engine loop
	while (isRunning)
	{
		//tESTING
		/*glClearColor(0.15f, 0.15f, 0.10f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.move(move);
		camera.updateMatrix();
		camera.Matrix(myshader, "camMatrix");
		model.Draw(myshader, camera);*/

		for (Layer* layer : layerStack)
		{
			layer->onUpdate();
		}

		window->onUpdate();
	}

}

void Engine::onEvent(Event& e)
{
	std::cout << e.toString() << std::endl;

	EventDispatcher dispatcher(e);

	dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

	for (auto it = layerStack.end(); it != layerStack.begin(); )
	{
		(*--it)->onEvent(e);
		if (e.isEventHandeled())
		{
			break;
		}
	}
}

void Engine::pushLayer(Layer* layer)
{
	layerStack.pushLayer(layer);
}

void Engine::pushOverlay(Layer* overlay)
{
	layerStack.pushOverlay(overlay);
}

bool Engine::onWindowClose(WindowCloseEvent& e)
{
	isRunning = false;
	return true;
}