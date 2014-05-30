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

RenderLightData::RenderLightData(glm::vec4 a, glm::vec4 d) : ambient(a), diffuse(d) {
  LoadUniformNames();
}

void RenderLightData::LoadUniformNames() {
  // Temporary -- Load these from some sort of config or stored data.
  uniformName = "light";
  ambientName = "globalAmbient";
  diffuseName = "diffuse";
  positionName = "position";
}