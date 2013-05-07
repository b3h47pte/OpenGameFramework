#pragma once
#ifndef _COMMON_GFX_H
#define _COMMON_GFX_H

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

#include "stdafx.h"

// OpenGL and GLEW
#include <gl\glew.h>
#include <gl\GL.h>
#include <gl\GLU.h>

#ifdef _WIN32
	#include <Windows.h>
#endif

// Core
#include "CoreExternal.h"

#include <iostream>
#include <vector>

// Define whether or not we're using SDL -- if not, we have to take care of creating contexts on each platform
// TODO: Eventually move this out into some sort of build system becaus this define will be useful in more than one subsystem
#define USE_SDL

#endif // _COMMON_GFX_H