#pragma once
#ifndef _MATERIALMANAGER_H
#define _MATERIALMANAGER_H

#include "CommonGfx.h"

/*
 * The material manager singleton object we will use to keep track of all the 
 * materials in the game. We will query this class to find the active materials.
 */
class MaterialManager {
public:
  static class MaterialManager* Get();

  ~MaterialManager();

  // Get Pointer to the material mapping so someone can look at all the materials
  const std::map<std::string, class Material*>* GetMaterialMapping() { return &mMaterialMapping; }

  // Registration of Materials.
  // There should never be a need to de-register a material.
  void RegisterMaterial(class Material*);
private:
  MaterialManager();

  // Mapping of Material ID to Material.
  std::map<std::string, class Material*> mMaterialMapping;
};

#endif