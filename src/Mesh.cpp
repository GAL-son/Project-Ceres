#include "include/Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures)
{
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	vao.vaoBind();

	VBO vbo(vertices);
	EBO ebo(indices);

	vao.linkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);					// Position
	vao.linkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));// Normal
	vao.linkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));// Color
	vao.linkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));// Texture UV

	vao.vaoUnbind();
	vbo.vboUnbind();
	ebo.eboUnbind();
}

void Mesh::draw
(
	Shader& shader, 
	Camera camera,
	glm::mat4 model,
	glm::vec3 translation,
	glm::quat rotation,
	glm::vec3 scale
)
{
	//::cout << "DRAW START" << textures.size() << std::endl;
	shader.activate();
	vao.vaoBind();

	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

	for(int i = 0; i < textures.size(); i++)
	{
		std::string num;
		TextureType type = textures[i].type;
		switch (type)
		{
		case TEXTURE_DIFFUSE:
			num = std::to_string(numDiffuse++);
			break;
		case TEXTURE_SPECULAR:
			num = std::to_string(numSpecular++);
			break;
		default:
			break;
		}
		textures[i].texUnit(shader, (textures[i].getTypeString() + num).c_str(), i);
		textures[i].textureBind();
	}

	// Take care of the camera Matrix
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.position.x, camera.position.y, camera.position.z);
	camera.Matrix(shader, "camMatrix");

	glm::mat4 transMat = glm::mat4(1.0f);
	glm::mat4 rotMat = glm::mat4(1.0f);
	glm::mat4 scaMat = glm::mat4(1.0f);

	transMat = glm::translate(transMat, translation);
	rotMat = glm::mat4_cast(rotation);
	scaMat = glm::scale(scaMat, scale);

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "translation"), 1, GL_FALSE, glm::value_ptr(transMat));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "rotation"), 1, GL_FALSE, glm::value_ptr(rotMat));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "scale"), 1, GL_FALSE, glm::value_ptr(scaMat));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(scaMat));

	// Draw the actual mesh
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}