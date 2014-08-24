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
uniform vec4 eyePosition;

layout (location = 0) out vec4 color;

// BLINN-PHONG BRDF: Blinn 1977 (Models of Light Reflection)
vec4 POINT_LIGHT_DISPATCH(LIGHT_PARAM_STRUCT inLight, BRDF_PARAM_STRUCT brdf) {
  vec4 N = normalize(vs_normal);
  vec4 L = normalize(inLight.lightPos - vs_position);
  vec4 E = normalize(eyePosition - vs_position);
  vec4 H = normalize(L+E);
  if (E.w < -0.001f) {
    return vec4(1.0f, 1.0f, 1.0f, 1.0f);
  }

  float d = max(0, dot(N,L));
  float s = pow(max(0,dot(N,H)), brdf.shininess);

  // Phong Lighting (Ambient and Diffuse)
  vec4 retColor = brdf.ambient * inLight.color + d * brdf.diffuse * inLight.color;

  // Blinn Specular Highlights (Specular)
  retColor += s * brdf.specular * inLight.color;

  return retColor;
}
void main() {
  // TODO: Dispatch based on type of light.
  color = POINT_LIGHT_DISPATCH(light, brdf);
}

