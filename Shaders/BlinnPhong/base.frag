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

// BLINN-PHONG BRDF: Blinn 1977 (Models of Light Reflection)

vec4 POINT_LIGHT_DISPATCH(LIGHT_PARAM_STRUCT light, BRDF_PARAM_STRUCT brdf) {
  vec4 toLight = normalize(light.lightPos - vs_position);
  float diff = max(dot(vs_normal, toLight),0);

  // Standard Phong Calculation
  vec4 color = brdf.ambient * light.color;

  // Additional Calculation for Specular by Blinn

  return color;
}

vec4 DIR_LIGHT_DISPATCH(LIGHT_PARAM_STRUCT light, BRDF_PARAM_STRUCT brdf) {
  vec4 color = light.color;

  return color;
}