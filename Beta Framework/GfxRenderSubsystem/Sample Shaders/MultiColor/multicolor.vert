#version 330

uniform mat4 projection_matrix, view_matrix, model_matrix;

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vNormal;
layout(location = 2) in vec2 vTexCoord;
layout(location = 3) in vec4 vColor;

out vec4 vs_color;

void main() {
	vs_color = vColor;
	gl_Position = projection_matrix * view_matrix * model_matrix * vPosition;
}
