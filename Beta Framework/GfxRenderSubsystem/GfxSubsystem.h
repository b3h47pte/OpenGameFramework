/*
 * Include this file if you're using this subsystem.
 *
 */

#pragma once
#ifndef _GFXSUBSYSTEM_H
#define _GFXSUBSYSTEM_H

#include "CommonGfx.h"

class IGfxWindow;

// GFXSUBSYSTEM_EXPORT defined in project properties for the GfxRenderSubsystem
#ifdef _WIN32
	#ifdef GFXSUBSYSTEM_EXPORT // inside DLL
		#define GFXSUBAPI __declspec(dllexport)
	#else // outside DLL
		#define GFXSUBAPI __declspec(dllimport)
	#endif  // GFXSUBSYTEM_EXPORT
#else
	#define GFXSUBAPI
#endif

class IGfxSubsystem: public ITickable
{
public:
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
	 * Error Management.
	 */ 
	enum EGfxErrorCodes {
		EGLEW_FAIL,
		EWINDOW_FAIL
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
	 * Whether or not to keep ticking -- will be set to false when SDL_QUIT is received.
	 */ 
	bool mStillRunning;
};

#endif // _GFXSUBSYSTEM_H