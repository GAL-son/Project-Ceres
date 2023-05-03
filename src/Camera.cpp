#include "include/Camera.h"

Camera::Camera(int widthpx, int heightpx, float nearPlane, float FarPlane, float FOV,  glm::vec3 position)
{
	Camera::position = position;	
	Camera::widthpx = widthpx;
	Camera::heightpx = heightpx;
	Camera::nearPlane = nearPlane;
	Camera::farPlane = farPlane;
	Camera::FOVdeg = FOV;
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Camera::updateMatrix()
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(position, position + orientation, up);
	//std::cout << position.x << std::endl;
	projection = glm::perspective(glm::radians(FOVdeg), (float)(widthpx / heightpx), nearPlane, farPlane);
	cameraMatrix = projection * view;
}

void Camera::draw() {}