#pragma once
#ifndef _GFXBACKEND_H
#define _GFXBACKEND_H

#include "CommonGfx.h"
#include "IRenderable.h"
#include "ILight.h"

class GfxBackend: public ITickable
{
public:
  GfxBackend(void);
  ~GfxBackend(void);

  // Register Renderable to make sure it gets rendered
  void RegisterRenderable(class IRenderable*);
  // Register lights and make sure to keep track of it in our scene.
  void RegisterLight(class ILight*);

  /*
   * Tick
   */ 
  virtual void PreTick();
  virtual bool ShouldTick()  { return true; }
  virtual void Tick(float);

  /*
   * Graphics API Initialization
   */ 
  virtual bool InitializeGraphicsAPI(int, int);

  /*
   * Viewport to render for.
   */
  virtual void SetActiveViewport(class IGfxViewport* in) { mActiveViewport = in; }

  /*
   * Used for any last minute things we need to do.
   */
  virtual bool PostInitialization();

private:

  /*
   * Texture Manager.
   */
  class TextureManager* mCurrentTextureManager;

  /*
   * Active Viewport.
   */
  class IGfxViewport* mActiveViewport;

  /*
   * BRDF Shader.
   */
  class GfxShaderInstance* mBRDFShader;
  
  /* 
   * Render function. 
   * Probably a naive generalization for now but will work for now as I slowly learn more about OpenGL and more advanced techniques.
   */
  void Render(float);

  /*
   * Intrusive Linked List for Rendering Objects.
   * I chose an intrusive linked list because: 
   *    1) Vectors: to store pointers would be slightly useless in this case since the spatial locality in grabbing the pointers would be ignored when we have to go all over memory
        to actually access the renderable object.
      2) Linked List: it may be very possible that an object will be added to the list and then removed in a short amount of time and I would not want to degrade performance due to
        a lot of removals which are inefficient in a linked list.
    Therefore, the intrusive linked list allows me to use a linked list without the degradation in performance when removing an element.
   */
  TIntrusiveLinkedList<IRenderable, offsetof(IRenderable, mBackendLink)> mRenderableList;

  /*
   * Intrusive Linked List for all Lights.
   */
  TIntrusiveLinkedList<ILight, offsetof(ILight, mBackendLink)> mLightList;

};


#endif // _GFXBACKEND_H
