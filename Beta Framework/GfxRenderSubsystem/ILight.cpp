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
  GfxShaders::LoadShader(GL_FRAGMENT_SHADER, GetLightFragShaderFile(), GetLightId());
  GfxShaders::LoadShader(GL_VERTEX_SHADER, GetLightVertexShaderFile(), GetLightId());
  FragShaderId = GfxShaders::GetShaderID(GL_FRAGMENT_SHADER, GetLightId());
  VertexShaderId = GfxShaders::GetShaderID(GL_VERTEX_SHADER, GetLightId());

  if (FragShaderId == -1 || VertexShaderId == -1) {
    std::cerr << "Vertex and/or Fragment Shader for the Light (" << GetLightId() << ") did not load properly." << std::endl;
    return;
  }

  ShaderInstance = GfxShaderInstance::CreateNewInstance(VertexShaderId, FragShaderId);
  ShaderProgramId = ShaderInstance->GetId();
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