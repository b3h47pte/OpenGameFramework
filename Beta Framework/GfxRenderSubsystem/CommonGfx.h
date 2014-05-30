#pragma once
#ifndef _COMMON_GFX_H
#define _COMMON_GFX_H

#include "stdafx.h"

// OpenGL and GLEW
#define NO_SDL_GLEXT
#ifdef _WIN32
#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#elif __APPLE__
#include <gl/glew.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#ifdef _WIN32
  #include <Windows.h>
#endif

// Other Defines Need for the Gfx Subsystem
#define GFX_MAX_VIEWPORTS  4

// Core
#include "CoreExternal.h"

#include <iostream>
#include <vector>
#include <map>

// Define whether or not we're using SDL -- if not, we have to take care of creating contexts on each platform
// TODO: Eventually move this out into some sort of build system becaus this define will be useful in more than one subsystem
#define USE_SDL

// Error Detection for OpenGL
inline void _DisplayOpenGLError(std::string command) {
  GLenum err = glGetError();
  if (err != GL_NO_ERROR) {
    std::cout << "OpenGL Error: " << err << " -- " << gluErrorString(err) << std::endl;
    std::cout << "Relevant Command: " << command << std::endl;
  }
}
#define OGL_CALL(x) x; _DisplayOpenGLError(#x);

#endif // _COMMON_GFX_H
