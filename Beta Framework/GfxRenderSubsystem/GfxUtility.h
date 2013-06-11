/*
 * Utility functions for the Gfx Render Subsystem.
 * Functionalities include: 
 *		- Reading in mesh data (OBJ, FBX, etc.)
 */ 

#pragma once
#ifndef _GFXUTILITY_H
#define _GFXUTILITY_H

#include "CommonGfx.h"

class IRenderable;

/*
 * Reads in an OBJ file and creates a MeshRenderable object. 
 * Creating an instance and registering the renderable/instance is up to the user.
 * Setting the proper shader data is also up to the user.
 */
IRenderable* GfxReadOBJFile(std::string);


#endif // _GFXUTILITY_H