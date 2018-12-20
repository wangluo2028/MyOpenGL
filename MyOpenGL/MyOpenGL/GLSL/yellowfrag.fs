#version 330 core
out vec4 FragColor;
//uniform vec4 ColorInFragment;
in vec4 OutColor;

void main()
{
	FragColor = OutColor;
}