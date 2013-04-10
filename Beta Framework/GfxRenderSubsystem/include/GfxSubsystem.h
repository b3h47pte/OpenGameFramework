/*
 * Include this file if you're using this subsystem.
 *
 */

#pragma once
#ifndef _GFXSUBSYSTEM_H
#define _GFXSUBSYSTEM_H

#include "common.h"

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

class IGfxSubsystem 
{
public:
};

/*
 * GfxSubsystem.
 * Exported from the DLL and is the only source of contact between the DLL and the game.
 */
class GfxSubsystem: public IGfxSubsystem
{
public:
	GfxSubsystem(void);
	~GfxSubsystem(void);
};

extern "C" GFXSUBAPI IGfxSubsystem* GetGfxSubsystem();

#endif // _GFXSUBSYSTEM_H