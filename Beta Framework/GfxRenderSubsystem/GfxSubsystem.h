/*
 * Include this file if you're using this subsystem.
 */

#pragma once
#ifndef _GFXSUBSYSTEM_H
#define _GFXSUBSYSTEM_H

#include "CommonGfx.h"

// Headers needed for classes using the Gfx subsystem.
#include "GfxViewport.h"
#include "GfxCamera.h"

class IGfxWindow;

class IGfxSubsystem: public ITickable
{
public:
  /*
   * Notify subsystem about a renderable that wants to get rendered.
   */
  virtual void RegisterRenderable(class IRenderable*) = 0;

  /*
   * Notify subsystem about a light that wants to get added to the scene.
   */
  virtual void RegisterLight(class ILight*) = 0;

  /*
   * Camera/Viewport Related. 
   * Default Number of Viewport: 1
   * Creates new viewports (must always have one). Max is stored in GFX_MAX_VIEWPORTS.
   * VIEWPORT ID IS ZERO-INDEXED.
   */
  virtual int SetViewportNumber(int) = 0;
  virtual class IGfxViewport* GetViewport(int) = 0;

};

extern "C"  IGfxSubsystem* GetGfxSubsystem(CAM_FACTORY_FCTN_PTR(camptr));

/*
 * GfxSubsystem handles window and OpenGL setup and will pass messages between the client and the graphics backend.
 * Will also detect input but will pass those messages out to somewhere else (whoever is configured to handle it).
 */
class GfxSubsystem: public IGfxSubsystem, public ErrorCatch
{
public:
  GfxSubsystem(CAM_FACTORY_FCTN_PTR(camptr));
  ~GfxSubsystem(void);

  /*
   * Backend Communication.
   */
  virtual void RegisterRenderable(class IRenderable*);
  virtual void RegisterLight(class ILight*);

  /*
   * Error Management.
   */ 
  enum EGfxErrorCodes {
    EGAPI_FAIL,
    EWINDOW_FAIL,
    EBACKEND_FAIL
  };

  virtual void DumpError (int) const;

  /*
   * Tick
   */ 
  virtual bool ShouldTick()  { return mStillRunning; }
  virtual void Tick(float);

  /*
   * Viewport.
   */ 
  virtual int SetViewportNumber(int);
  virtual class IGfxViewport* GetViewport(int);
private:
  /*
   * mWindow sets up the window either using SDL or using the OS specific way.
   */
  IGfxWindow* mWindow;

  /*
   * Whether or not to keep ticking -- will be set to false when SDL_QUIT is received (or more accurately -- when we want to start rendering)
   */ 
  bool mStillRunning;

  /*
   * Backend that cares all of the dirty work.
   */ 
  class GfxBackend* mBackend;

  /*
   * Viewports. 
   */
  int mActiveViewports;
  class IGfxViewport* mAllViewports[GFX_MAX_VIEWPORTS];

  /*
   * Camera Factory Function.
   */
  CAM_FACTORY_FCTN_PTR(mCameraFactoryFunc);
};

#endif // _GFXSUBSYSTEM_H
