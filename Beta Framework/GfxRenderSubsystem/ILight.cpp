#include <iostream>
#include <sstream>
#include "ILight.h"
#include "GfxShaders.h"
#include "GfxShaderInstance.h"

int ILight::CurrentLightCount = 0;

std::string ILight::GetNewLightId() {
  std::ostringstream sig;
  sig << "__ogf_light_" << ILight::ReserveLight();
  return sig.str();
}

void ILight::InitializeLight() {
  // Load the shader file.  
  SetLightId(ILight::GetNewLightId());
  data.position = GetPosition();
}

/************************************************************************/
/* Render Light Data Information.                                       */
/************************************************************************/

RenderLightData::RenderLightData() {
  LoadUniformNames();
}

RenderLightData::RenderLightData(glm::vec4 c) : color(c) {
  LoadUniformNames();
}

void RenderLightData::LoadUniformNames() {
  // Temporary -- Load these from some sort of config or stored data.
  uniformName = "light";
  colorName = "color";
  positionName = "lightPos";
}