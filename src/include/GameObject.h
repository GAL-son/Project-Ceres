#ifndef GAMEOBJECT_CLASS_H
#define GAMEOBJECT_CLASS_H

#include "Object.h"
#include "Model.h"

class GameObject : Object
{
public:
	Model& activeModel;

	GameObject();

	void draw();

private:
	std::vector<Model> models;
};


#endif // !GAMEOBJECT_CLASS_H
