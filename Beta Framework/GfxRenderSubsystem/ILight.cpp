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
  GfxShaders::LoadShader(GL_FRAGMENT_SHADER, GetLightFragShaderFile(), GetLightId());
  GfxShaders::LoadShader(GL_VERTEX_SHADER, GetLightVertexShaderFile(), GetLightId());
  FragShaderId = GfxShaders::GetShaderID(GL_FRAGMENT_SHADER, GetLightId());
  VertexShaderId = GfxShaders::GetShaderID(GL_VERTEX_SHADER, GetLightId());

  if (FragShaderId == -1 || VertexShaderId == -1) {
    std::cerr << "Vertex and/or Fragment Shader for the Light (" << GetLightId() << ") did not load properly." << std::endl;
    return;
  }

  ShaderProgramId = OGL_CALL(glCreateProgram());
  OGL_CALL(glAttachShader(ShaderProgramId, VertexShaderId));
  OGL_CALL(glAttachShader(ShaderProgramId, FragShaderId));
  OGL_CALL(glLinkProgram(ShaderProgramId));
  OGL_CALL(glDetachShader(ShaderProgramId, VertexShaderId));
  OGL_CALL(glDetachShader(ShaderProgramId, FragShaderId));
}