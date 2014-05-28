#version 330

uniform mat4 projection_matrix, view_matrix, model_matrix;

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vNormal;
layout(location = 2) in vec2 vTexCoord;

struct LightProperties {
  vec4 globalAmbient;
  vec4 diffuse;
  vec4 position;
};
uniform LightProperties light;

out Data {
  vec4 lightDir;
  vec4 normal;
} DataOut;

void main() {
	gl_Position = projection_matrix * view_matrix * model_matrix * vPosition;

  DataOut.lightDir = normalize(light.position - vPosition);
  DataOut.normal = normalize(vNormal);
}
