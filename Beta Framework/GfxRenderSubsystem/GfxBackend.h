#pragma once
#ifndef _GFXBACKEND_H
#define _GFXBACKEND_H

#include "CommonGfx.h"

class GfxBackend: public ITickable
{
public:
	GfxBackend(void);
	~GfxBackend(void);

	// Register Renderable to make sure it gets rendered
	void RegisterRenderable(class IRenderable*);

	/*
	 * Tick
	 */ 
	virtual bool ShouldTick()  { return true; }
	virtual void Tick(float);

private:
};

#endif // _GFXBACKEND_H