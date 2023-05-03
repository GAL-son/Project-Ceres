#include "include/Texture.h"

Texture::Texture(const char* imagePath, TextureType texType, GLuint slot)
{
	// Assign texture type
	type = texType;

	// Load image using stbi
	int imgWidth, imgHeight, numColCh;
	stbi_set_flip_vertically_on_load(true);

	unsigned char* bytes = stbi_load(imagePath, &imgWidth, &imgHeight, &numColCh, 0);

	//Generate texure object
	glGenTextures(1, &ID);

	//Assign texture to texture unit
	glActiveTexture(GL_TEXTURE0 + slot);
	unit = slot;

	glBindTexture(GL_TEXTURE_2D, ID);

	// Interpolation between pixels
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Behaviour on edges of texture image
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	switch (numColCh)
	{
	case 4:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
		break;
	case 3:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
		break;
	case 1:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RED, GL_UNSIGNED_BYTE, bytes);
		break;
	default:
		throw std::invalid_argument("Failed to recognize texture type");
		break;
	}

	// Generate MipMaps
	glGenerateMipmap(GL_TEXTURE_2D);

	// Free unsused memory
	stbi_image_free(bytes);
	textureUnbind();
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	GLuint texUniform = glGetUniformLocation(shader.ID, uniform);
	shader.activate();
	glUniform1i(texUniform, unit);
}

void Texture::textureBind()
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::textureUnbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::textureDelete()
{
	glDeleteTextures(1, &ID);
}

std::string Texture::getTypeString()
{
	switch (type)
	{
	case TEXTURE_DIFFUSE:
		return "diffuse";
		break;
	case TEXTURE_SPECULAR:
		return "specular";
		break;
	}

	return "";
}

