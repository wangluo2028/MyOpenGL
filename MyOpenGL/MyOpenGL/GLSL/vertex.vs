#version 330 core
layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aColor;
layout(location=2) in vec2 aTexCoord;
out vec4 OutColor;
out vec2 OutTexCoord;

uniform mat4 ObjectTransform;

void main()
{
	gl_Position = ObjectTransform * vec4(aPos, 1.0);
	OutColor = vec4(aColor, 1.0);
	OutTexCoord = aTexCoord;
}