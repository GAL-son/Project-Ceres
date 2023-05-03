#ifndef OBJECT_CLASS_H
#define OBJECT_CLASS_H

#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>


class Object
{
public:
	glm::vec3 position;
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::quat rotation = glm::quat(1.0f,0.0f, 0.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	virtual void draw() = 0;
	void move(glm::vec3 direction);
	void moveX(float x);
};

#endif // !OBJECT_CLASS_H
