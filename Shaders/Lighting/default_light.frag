#version 330

// DEFAULT LIGHT: Phong Shader.

struct Material {
  vec4 emissive;
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  float shininess;
};

struct LightProperties {
  vec4 globalAmbient;
  vec4 diffuse;
  vec4 position;
};

in Data {
  vec4 lightDir;
  vec4 normal;
} DataIn;

uniform Material mat;
uniform LightProperties light;

layout (location = 0) out vec4 color;

void main() {
	// Emissive
  vec4 fragColor = mat.emissive;

  // Ambient
  fragColor += light.globalAmbient * mat.ambient;

	// Diffuse
  fragColor += (mat.diffuse * light.diffuse * max(dot(DataIn.normal, DataIn.lightDir), 0.0f));

	// Specular

  // Output
  color = fragColor;
}
