#pragma once
#ifndef _IRENDERABLE_H
#define _IRENDERABLE_H

#include "CommonGfx.h"

/*
 * A renderable object (interface). 
 * If an object is renderable, it must be registered with the Gfx Subsystem which will handle making sure it gets rendered.
 * However, since we want to keep this as modular as possible, I don't specify in what format the renderable has to store its data so at is very primitive state
 *		I will just be reading in vertices/triangles, normals, various textures/color data via some interface functions and rendering that. 
 * EVENTUALLY, I will probably implement something to take care of animations and the like -- maybe allow for more specifics to make OBJ/FBX data more efficient (not sure how that'd work).
 */
class GFXSUBAPI IRenderable: public ITickable
{
public:
	IRenderable();
	virtual ~IRenderable();

	friend class GfxBackend;
private:
	/*
	 * Whether or not this renderable has already been registered by the backend.
	 * NEVER CHANGE THIS VARIABLE WITHIN IRENDERABLE. 
	 */
	bool mIsRegistered;

	/*
	 * 
	 */
};

#endif // _IRENDERABLE_H