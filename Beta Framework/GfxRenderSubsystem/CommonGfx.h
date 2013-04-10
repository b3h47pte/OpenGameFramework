#pragma once
#ifndef _COMMON_GFX_H
#define _COMMON_GFX_H

#include "stdafx.h"

// OpenGL and GLEW
#include <gl\glew.h>
#include <gl\GL.h>
#include <gl\GLU.h>

#ifdef _WIN32
	#include <Windows.h>
#endif

// Core
#include "ErrorCatch.h"
#include "ITickable.h"

#include <iostream>

// Define whether or not we're using SDL -- if not, we have to take care of creating contexts on each platform
// TODO: Eventually move this out into some sort of build system becaus this define will be useful in more than one subsystem
#define USE_SDL

#endif // _COMMON_GFX_H