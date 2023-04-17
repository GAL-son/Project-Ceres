#include "EBO.h"

EBO::EBO(std::vector <GLuint> indecies)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indecies.size() * sizeof(GLuint), indecies.data(), GL_STATIC_DRAW);
}
