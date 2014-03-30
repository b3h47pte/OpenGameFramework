#include <iostream>
#include <sstream>
#include "ILight.h"
#include "GfxShaders.h"

std::string ILight::GetNewLightId() {
  std::ostringstream sig;
  sig << "__ogf_light_" << ILight::ReserveLight();
  return sig.str();
}

void ILight::InitializeLight() {
  // Load the shader file.  
  GfxShaders::LoadShader(GL_FRAGMENT_SHADER, GetLightShaderFile(),
                         ILight::GetNewLightId());
}

void ILight::InsertLightSubroutineType(std::string& curShader) {
  std::string repText = "%LIGHT_SUBROUTINE_TYPE%";
  curShader.replace(curShader.find(repText), repText.size(), 
                    ILight::GetLightSubroutineType());
}

void ILight::InsertSubroutineSignature(std::string& curShader) {
  std::ostringstream sig;
  sig << "subroutine vec4 " << ILight::GetLightSubroutineType() << "();" 
    << std::endl;

  std::string repText = "%LIGHT_SUBROUTINE_SIGNATURE%";
  curShader.replace(curShader.find(repText), repText.size(), sig.str());
}


