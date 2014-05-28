#pragma once
#ifndef _ILIGHT_H
#define _ILIGHT_H

#include "CommonGfx.h"

/*
 * Defines a standard interface for how the graphics subsystem will interact
 * with lights. This gives users the ability to easily add their own type of 
 * lights.
 */
class ILight : public WorldObject {
public:
  ILight(): isRegistered(false) {}
  ILight(glm::vec4 pos) : WorldObject(pos), isRegistered(false) {}
  virtual ~ILight() {}

  virtual int GetShaderID() {
    return ShaderProgramId;
  }

  // Whether or not the light has been registered.
  bool GetIsRegistered() {
    return isRegistered;
  }

  friend class GfxBackend;
protected:
  virtual std::string GetLightVertexShaderFile() { 
    return "Lighting/defaultlight.vert";
  }

  virtual std::string GetLightFragShaderFile() {
    return "Lighting/defaultlight.frag";
  }

  static std::string GetNewLightId();
  static int CurrentLightCount;
  static int ReserveLight() {
    return ++CurrentLightCount;
  }

  std::string GetLightId() {
    return LightId;
  }

  void SetLightId(std::string& id) {
    LightId = id;
  }

private:
  int VertexShaderId;
  int FragShaderId;
  int ShaderProgramId;

  std::string LightId;
  bool isRegistered;
  void SetIsRegistered(bool b) {
    isRegistered = b;
  }

  // Initializes the shader for the light.
  // Loads the shader source, replaces variables as necessary inside the source.
  // Sends it to the shader manager for loading.
  virtual void InitializeLight();

  /*
  * Link in the linked list of all lights.
  */
  TIntrusiveLink<ILight> mBackendLink;
};


#endif // _ILIGHT_H
