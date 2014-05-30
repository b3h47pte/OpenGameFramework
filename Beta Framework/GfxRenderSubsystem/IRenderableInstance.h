#pragma once
#ifndef _IRENDERABLEINSTANCE_H
#define _IRENDERABLEINSTANCE_H

#include "CommonGfx.h"

class IRenderableInstance:public WorldObject
{
public:
  IRenderableInstance(class IRenderable*, WorldObject*);
  virtual ~IRenderableInstance(void);

  /*
   * Give users flexibility to do other stuff when the renderable gets registered. (Called AFTER registration).
   */
  virtual void OnRegistration();

  /*
   * Unregister us from the link (backend). Called AFTER deregistration.
   */
  void UnregisterRenderableInstance();
  virtual void OnDeregistration();

  friend class IRenderable;
  friend class GfxBackend;

  /*
   * Various Accessor Functions.
   */
  const IRenderable* GetParentRenderable() const { return mParentRenderable; }

protected:
  /*
   * Render function. Called in the Gfx Backend Render loop.
   */
  virtual void OnRender();
  virtual void PrepareRender(class GfxShaderInstance*);
  virtual void FinishRender();

private:
  // Texture Location Count -- 0 to n...will allow us to control which texture unit gets assigned to what sampler in the shader.
  unsigned int mTextureLocationCount;

  /*
   * What is the difference between Parent Renderable and Parent Object?
   * Parent Renderable -- Parent renderable holds the mesh's data (material, mesh data, etc)
   * Parent Object -- The object that this renderable instance is attached to (where we get parent orientation/location from)
   */
  IRenderable*  mParentRenderable;
  WorldObject*  mParentObject;

  /*
   * Link in the linked list of all renderable instances.
   * NOTE: This gives warning C241
   * Going to pragma it out because it should not be an issue since the variable is private and no-one outside of this DLL should be touching it
   */
  TIntrusiveLink<IRenderableInstance> mInstanceLink;

  /*
   * Whether or not this renderable has already been registered by the backend.
   * NEVER CHANGE THIS VARIABLE WITHIN IRENDERABLEINSTANCE -- aside from the unregister function.
   */
  bool mIsRegistered;

  /*
   * Overridable Render Functions. PreRender/PostRender can (and should) be overriden. 
   * Gives user some flexibility in doing some extra stuff before/after this object gets rendered.
   */
  virtual void PreRender() = 0;
  virtual void PostRender() = 0;

  /*
   * Material Instance List. Holds the material instances that are in use by this renderable instance.
   */
  std::vector<class MaterialInstance*> mMaterialList;
};

#endif // _IRENDERABLEINSTANCE_H
