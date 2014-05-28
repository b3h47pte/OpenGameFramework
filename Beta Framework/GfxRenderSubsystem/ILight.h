#pragma once
#ifndef _ILIGHT_H
#define _ILIGHT_H

#include "CommonGfx.h"

struct RenderLightData {
  RenderLightData() {}
  RenderLightData(glm::vec4 a, glm::vec4 d) : ambient(a), diffuse(d){
  }

  glm::vec4 ambient;
  glm::vec4 diffuse;
  glm::vec4 position;
};

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

  virtual class GfxShaderInstance* GetShader() {
    return ShaderInstance;
  }

  // Whether or not the light has been registered.
  bool GetIsRegistered() {
    return isRegistered;
  }

  /*
   * Retrieve light data for rendering.
   */
  const RenderLightData* GetLightData() const {
    return &data;
  }

  void SetLightData(RenderLightData& inData) {
    data = inData;
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
  class GfxShaderInstance* ShaderInstance;

  std::string LightId;
  bool isRegistered;
  void SetIsRegistered(bool b) {
    isRegistered = b;
  }
  
  // Aggregate Data that will be used for rendering
  RenderLightData data;

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
