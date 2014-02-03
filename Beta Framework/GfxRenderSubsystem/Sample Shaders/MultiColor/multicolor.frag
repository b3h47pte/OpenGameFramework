#version 330
uniform vec4 ambientLight;

in vec4 vs_color;

layout (location = 0) out vec4 color;

void main() {
  color = vs_color;
}
