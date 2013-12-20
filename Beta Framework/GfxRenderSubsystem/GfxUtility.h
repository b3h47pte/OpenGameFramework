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

#ifndef GFXUTILITY_NOOBJ
/*
 * Reads in an OBJ file and creates a MeshRenderable object. 
 * Creating an instance and registering the renderable/instance is up to the user.
 * Setting the proper shader data is also up to the user.
 */
IRenderable* GfxReadOBJFile(std::string);

#endif

#ifndef GFXUTILITY_NOFREEIMAGE

#include "FreeImage.h"

/*
 * Will read an image and register it with the texture manager.
 */
class ITexture* CreateTextureFromImage(const std::string&, const std::string&);

#endif //  GFXUTILITY_NOFREEIMAGE


#endif // _GFXUTILITY_H
