#version 330

uniform samplerCube tex;

in vec3 vs_tex_coord;

layout (location = 0) out vec4 color;

void main() {
	color = texture(tex, vs_tex_coord).rgba;
}
