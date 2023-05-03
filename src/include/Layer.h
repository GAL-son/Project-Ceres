#ifndef LAYER_CLASS_H
#define LAYER_CLASS_H

#include "Events/Event.h"

class Layer
{
public:
	Layer(const std::string& name = "layer");
	virtual ~Layer();

	virtual void onAttach() {};
	virtual void onDetach() {};
	virtual void onUpdate() {};
	virtual void onEvent(Event& event) {};

	inline const std::string& getName() const { return layerDebugName; }

private:
	std::string layerDebugName;
};


#endif // !LAYER_CLASS_H
