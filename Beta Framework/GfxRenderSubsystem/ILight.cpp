#include <iostream>
#include <sstream>
#include "ILight.h"
#include "GfxShaders.h"

int ILight::CurrentLightCount = 0;

std::string ILight::GetNewLightId() {
  std::ostringstream sig;
  sig << "__ogf_light_" << ILight::ReserveLight();
  return sig.str();
}

void ILight::InitializeLight() {
  // Load the shader file.  
  SetLightId(ILight::GetNewLightId());
  GfxShaders::LoadShader(GL_FRAGMENT_SHADER, GetLightShaderFile(),
                         LightId);
  LightShaderId = GfxShaders::GetShaderID(GL_FRAGMENT_SHADER, GetLightId());
}