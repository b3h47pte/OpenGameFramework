#version 330 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vNormal;
layout(location = 2) in vec2 vTexCoord;

out vec4 color;

void main() {
	color = vec4(1.f, 0.f, 0.f, 0.f);
	gl_Position = vPosition;
}