#version 330

uniform mat4 projection_matrix, view_matrix, model_matrix;

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vNormal;
layout(location = 2) in vec2 vTexCoord;

out vec2 vs_tex_coord;

void main() {
	gl_Position = projection_matrix * view_matrix * model_matrix * vPosition;
	vs_tex_coord = vTexCoord;
}
