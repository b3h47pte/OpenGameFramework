/*
 * Include this file if you're using this subsystem.
 */

#pragma once
#ifndef _GFXSUBSYSTEM_H
#define _GFXSUBSYSTEM_H

#include "CommonGfx.h"
#include "IRenderable.h"
#include "MeshRenderable.h"

class IGfxWindow;

class IGfxSubsystem: public ITickable
{
public:
	virtual void RegisterRenderable(IRenderable*) = 0;
};

extern "C" GFXSUBAPI IGfxSubsystem* GetGfxSubsystem();

/*
 * GfxSubsystem handles window and OpenGL setup and will pass messages between the client and the graphics backend.
 * Will also detect input but will pass those messages out to somewhere else (whoever is configured to handle it).
 */
class GfxSubsystem: public IGfxSubsystem, public ErrorCatch
{
public:
	GfxSubsystem(void);
	~GfxSubsystem(void);

	/*
	 * Backend Communication.
	 */
	virtual void RegisterRenderable(IRenderable*);

	/*
	 * Error Management.
	 */ 
	enum EGfxErrorCodes {
		EGLEW_FAIL,
		EWINDOW_FAIL,
		EBACKEND_FAIL
	};

	virtual void DumpError (int) const;

	/*
	 * Tick
	 */ 
	virtual bool ShouldTick()  { return mStillRunning; }
	virtual void Tick(float);
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
};

#endif // _GFXSUBSYSTEM_H