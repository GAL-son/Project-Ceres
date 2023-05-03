#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Object.h"
#include "Shader.h"

class Camera : public Object
{
public:
	glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	int widthpx, heightpx;
	float nearPlane, farPlane;
	float FOVdeg;

	Camera(int widthpx, int heightpx, float nearPlane, float FarPlane, 
		float FOV = 45.0f, 
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));

	void Matrix(Shader& shader, const char* uniform);
	void updateMatrix();
	void draw();

};

#endif // !CAMERA_CLASS_H
