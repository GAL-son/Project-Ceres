#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>

#include "VBO.h"

class VAO
{
public:
	GLuint ID;

	VAO();

	void linkAttrib(VBO& vbo, GLuint layout, GLuint numOfComponents, GLenum type, GLsizeiptr stride, void* offset);
	void vaoBind();
	void vaoUnbind();
	void vaoDelete();
};

#endif // !VAO_CLASS_H