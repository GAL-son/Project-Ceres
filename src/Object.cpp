#include "include/Object.h"

void Object::move(glm::vec3 direcrion)
{
	position += direcrion;
}

void Object::moveX(float x)
{
	position.x += x;
}