#version 330 core

uniform mat4 projection_matrix;

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vNormal;
layout(location = 2) in vec2 vTexCoord;

out vec4 vs_color;

void main() {
	vs_color = vec4(0.f, 1.f, 1.f, 1.f);
	gl_Position = projection_matrix * vPosition;
}