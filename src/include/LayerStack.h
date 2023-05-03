#ifndef LAYER_STACK_CLASS_H
#define LAYER_STACK_CLASS_H

#include <vector>
#include "Layer.h"

class LayerStack
{
public:
	LayerStack();
	~LayerStack();

	void pushLayer(Layer* layer);
	void pushOverlay(Layer* overlay);
	void popLayer(Layer* layer);
	void popOverlay(Layer* overlay);

	std::vector<Layer*>::iterator begin() { return layers.begin(); }
	std::vector<Layer*>::iterator end() { return layers.end(); }

private:
	std::vector<Layer*> layers;
	std::vector<Layer*>::iterator layerInsert;
};


#endif // !LAYER_STACK_CLASS_H
