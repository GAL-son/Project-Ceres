#include "include/Shader.h"

std::string getFileContents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return contents;
	}
	std::cout << "ERROR LOADING " << filename << "FILE" << std::endl;
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// Read Shaders source code to const char*
	std::string vertexCode = getFileContents(vertexFile);
	std::string fragmentCode = getFileContents(fragmentFile);
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// DEBUG
	//std::cout << vertexSource << std::endl;
	//std::cout << fragmentSource << std::endl;

	// Create Shaders
	GLuint vertexID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

	// Link source code to shaders
	glShaderSource(vertexID, 1, &vertexSource, NULL);
	glShaderSource(fragmentID, 1, &fragmentSource, NULL);

	// Compile Vertex shader
	glCompileShader(vertexID);
	compileErrors(vertexID, "VERTEX");

	// Compile Fragment Shader
	glCompileShader(fragmentID);
	compileErrors(fragmentID, "FRAGMENT");

	ID = glCreateProgram();

	glAttachShader(ID, vertexID);
	glAttachShader(ID, fragmentID);

	glLinkProgram(ID);
	compileErrors(ID, "PROGRAM");

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
}

void Shader::activate()
{
	glUseProgram(ID);
}

void Shader::deleteShader()
{
	glDeleteProgram(ID);
}

void Shader::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];

	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);

		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1042, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for: " << type << "\n" << std::endl;
			std::cout << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);

		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1042, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for: " << type << "\n" << std::endl;
			std::cout << infoLog << std::endl;
		}
	}
}