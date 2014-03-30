#pragma once
#ifndef _ILIGHT_H
#define _ILIGHT_H

#include "CommonGfx.h"

/*
 * Defines a standard interface for how the graphics subsystem will interact
 * with lights. This gives users the ability to easily add their own type of 
 * lights.
 *
 * Assumption: All lights will have their own subroutine inside their own
 *             shader program. The type of the subroutine will be defined
 *             by the graphics backend. When rendering an object, if it is 
 *             affected by a light, then the light's subroutine will be called.
 *             Each type of light should have its own subroutine and each subroutine
 *             will only be registered once.
 *
 * Light-Specific Details: 
 *             A light will require per-light details that should be passed
 *             to the shader via uniforms. The light's implementation should take
 *             care of those details and should make an effort to avoid using
 *             uniform names that may collide. 
 *          
 * Utility: Provide utility functions that will:
 *            1) obfuscate uniform names if required.
 *            2) insert the subroutine signature to the shader.
 */
class ILight {
public:
  ILight() {}
  virtual ~ILight() {}

  // Initializes the shader for the light.
  // Loads the shader source, replaces variables as necessary inside the source.
  // Sends it to the shader manager for loading.
  virtual void InitializeLight();

  // Subroutine Type for Lights. 
  // Used to define the subroutine type for all lights in light GLSL files
  // but is also necessary for other shaders so that we know what uniform
  // variable we want to be able to pass into shaders.
  static std::string GetLightSubroutineType() { return "ogfLight"; }
  static void InsertLightSubroutineType(std::string& curShader);

  // Inserts the subroutine signature type.
  static void InsertSubroutineSignature(std::string& curShader);
protected:
  virtual std::string GetLightShaderFile() { 
    return "base_light.frag";
  }
private:
  std::string GetNewLightId();
  int ReserveLight() {
    return 0;
  }
};


#endif // _ILIGHT_H
