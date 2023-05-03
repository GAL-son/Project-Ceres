#version 330 core

// From Vertex Shader
in vec3 crntPos;
in vec3 normal;
in vec3 color;
in vec2 texCoord;

// Texture uniforms
uniform sampler2D diffuse0;
uniform sampler2D specular0;

//Output color
out vec4 FragColor;

void main()
{
	FragColor =  texture(diffuse0, texCoord);
}