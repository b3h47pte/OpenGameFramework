#version 330

uniform mat4 projection_matrix, view_matrix, model_matrix;

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vNormal;
layout(location = 2) in vec2 vTexCoord;

out vec4 vs_position;
out vec4 vs_normal;

void main() {
	gl_Position = projection_matrix * view_matrix * model_matrix * vPosition;
  vs_position = vPosition;
  vs_normal = vNormal;
}
