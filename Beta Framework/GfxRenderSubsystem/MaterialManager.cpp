#include "MaterialManager.h"
#include "Material.h"

MaterialManager::MaterialManager() {
}

MaterialManager::~MaterialManager() {
}

MaterialManager* MaterialManager::Get() {
  static MaterialManager* mng = []() {
    MaterialManager* tm = new MaterialManager();
    return tm;
  }();
  return mng;
}

/*
 * Notifies the material manager about a new material. Does nothing besides checking for 
 * a duplication of material ID.
 */
void MaterialManager::RegisterMaterial(class Material* inMaterial) {
  if (mMaterialMapping.find(inMaterial->GetUniqueId()) != mMaterialMapping.end()) {
    ERROR_PRINT("Found two material with the same ID: " + inMaterial->GetUniqueId());
    // TODO: We shouldn't be allowed to continue here.
    return;
  }
  mMaterialMapping[inMaterial->GetUniqueId()] = inMaterial;
}