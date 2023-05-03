#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "Shader.h"

enum TextureType {
	TEXTURE_DIFFUSE,
	TEXTURE_SPECULAR,
};

class Texture
{
public:
	GLuint ID;
	TextureType type;
	GLuint unit;

	Texture(const char* imagePath, TextureType texType, GLuint unit);

	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void textureBind();
	void textureUnbind();
	void textureDelete();

	std::string getTypeString();
};

#endif // !TEXTURE_CLASS_H
