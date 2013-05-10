#pragma once
#ifndef _MESHRENDERABLEINSTANCE_H
#define _MESHRENDERABLEINSTANCE_H

#include "CommonGfx.h"
#include "IRenderableInstance.h"

class GFXSUBAPI MeshRenderableInstance: public IRenderableInstance
{
public:
	MeshRenderableInstance(class IRenderable*, WorldObject*);
	virtual ~MeshRenderableInstance(void);

private:

	/*
	 * Render function. Called in the Gfx Backend Render loop.
	 */
	virtual void OnRender();

	/*
	 * Overridable Render Functions. PreRender/PostRender can (and should) be overriden. 
	 * Gives user some flexibility in doing some extra stuff before/after this object gets rendered.
	 */
	virtual void PreRender() {}
	virtual void PostRender() {}

};

#endif // _MESHRENDERABLEINSTANCE_H

