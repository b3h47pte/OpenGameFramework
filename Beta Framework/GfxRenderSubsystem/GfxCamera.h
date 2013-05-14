#pragma once
#ifndef _GFXCAMERA_H
#define _GFXCAMERA_H
#pragma warning( push )

#include "CommonGfx.h"

class GFXSUBAPI IGfxCamera: public WorldObject {
public:
	virtual float GetFOV() const = 0;
	virtual void SetFOV(float) = 0;

	virtual float GetAspectRatio() const = 0;
	virtual void SetAspectRatio(float) = 0;
};

/*
 * NOT MEANT TO BE A COMPREHENSIVE CAMERA CLASS. More specific details should be handled by the engine/game.
 * In fact it might be better for games to just create their own camera class based off of the Camera interface but this is here just for convenience.
 */
class GfxCamera: public IGfxCamera
{
public:
	GfxCamera(void);
	~GfxCamera(void);

	virtual float GetFOV() const { return mFOV; }
	virtual void SetFOV(float in) {mFOV = in;}

	virtual float GetAspectRatio() const { return mAspectRatio; }
	virtual void SetAspectRatio(float in) { mAspectRatio = in; }

private:
	/*
	 * FOV
	 */
	float mFOV;

	/*
	 * Aspect Ratio
	 */
	float mAspectRatio;
};

#define CAM_FACTORY_FCTN_PTR(var) IGfxCamera* (*var) (float, float)

extern "C" GFXSUBAPI IGfxCamera* GFX_CREATE_DEFAULT_CAMERA(float inFOV, float inAR);
#endif // _GFXCAMERA_H