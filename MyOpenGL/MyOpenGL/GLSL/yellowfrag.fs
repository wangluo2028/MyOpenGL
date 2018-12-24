#version 330 core
out vec4 FragColor;
//uniform vec4 ColorInFragment;
in vec4 OutColor;
in vec2 OutTexCoord;

uniform sampler2D MyTexture0;
uniform sampler2D MyTexture1;

void main()
{
	FragColor = mix( texture(MyTexture0, OutTexCoord), texture(MyTexture1, OutTexCoord), 0.2);
}