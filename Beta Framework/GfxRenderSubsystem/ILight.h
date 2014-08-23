#pragma once
#ifndef _ILIGHT_H
#define _ILIGHT_H

#include "CommonGfx.h"

struct RenderLightData {
  RenderLightData();
  RenderLightData::RenderLightData(glm::vec4 c);

  glm::vec4 color;
  std::string colorName;

  glm::vec4 position;
  std::string positionName;
  
  std::string uniformName;
 
private:
  void LoadUniformNames();
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
