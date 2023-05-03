#include "include/VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

void VAO::linkAttrib(VBO& vbo, GLuint layout, GLuint numOfComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	vbo.vboBind();

	glVertexAttribPointer(layout, numOfComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);

	vbo.vboUnbind();
}

void VAO::vaoBind()
{
	glBindVertexArray(ID);
}

void VAO::vaoUnbind()
{
	glBindVertexArray(0);
}

void VAO::vaoDelete()
{
	glDeleteVertexArrays(1, &ID);
}
