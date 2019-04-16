#version 430 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec2 TexCoords;
layout(location = 3) in vec3 Tangent;
layout(location = 4) in vec3 Bitangent;

uniform mat4 viewProjectionMatrix;

void main()
{		
	gl_Position = viewProjectionMatrix * vec4(Position.xyz,1);
}