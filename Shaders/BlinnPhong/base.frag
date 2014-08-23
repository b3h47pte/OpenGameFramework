#version 330

struct LIGHT_PARAM_STRUCT {
  vec4 color;
  vec4 lightPos;
  int lightId;
};

struct BRDF_PARAM_STRUCT {
  vec4 diffuse;
  vec4 specular;
  vec4 ambient;
  float shininess;
};

in vec4 vs_position;
in vec4 vs_normal;

uniform LIGHT_PARAM_STRUCT light;
uniform BRDF_PARAM_STRUCT brdf;
layout (location = 0) out vec4 color;

// BLINN-PHONG BRDF: Blinn 1977 (Models of Light Reflection)
vec4 POINT_LIGHT_DISPATCH(LIGHT_PARAM_STRUCT inLight, BRDF_PARAM_STRUCT brdf) {
  vec4 toLight = normalize(light.lightPos - vs_position);
  float diff = max(dot(vs_normal, toLight),0);
  // Standard Phong Calculation
  vec4 plColor = brdf.ambient * light.color + diff * brdf.diffuse * light.color;

  // Additional Calculation for Specular by Blinn

  return plColor;
}
void main() {
  // TODO: Dispatch based on type of light.
  color = POINT_LIGHT_DISPATCH(light, brdf);
}

