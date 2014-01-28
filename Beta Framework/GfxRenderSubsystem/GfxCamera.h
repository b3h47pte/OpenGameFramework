#pragma once
#ifndef _GFXCAMERA_H
#define _GFXCAMERA_H

#include "CommonGfx.h"

class  IGfxCamera: public WorldObject {
public:
	virtual float GetFOV() const = 0;
	virtual void SetFOV(float) = 0;

	virtual float GetAspectRatio() const = 0;
	virtual void SetAspectRatio(float) = 0;

	virtual float GetZNear() const = 0;
	virtual void SetZNear(float) = 0;

	virtual float GetZFar() const = 0;
	virtual void SetZFar(float) = 0;

  virtual glm::mat4 GetProjectionMatrix() const = 0;
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

	virtual float GetZNear() const { return mZNear; }
	virtual void SetZNear(float in) { mZNear = in; }

	virtual float GetZFar() const { return mZFar; }
	virtual void SetZFar(float in) { mZFar = in; }

  virtual glm::mat4 GetProjectionMatrix() const {
    return glm::perspective(GetFOV(), GetAspectRatio(), GetZNear(), GetZFar());
  }

protected:
  virtual void UpdateTransformationMatrix();

private:
	/*
	 * FOV (Y-Direction)
	 */
	float mFOV;

	/*
	 * Aspect Ratio
	 */
	float mAspectRatio;

	/*
	 * Z-Far/Near. Defaults to 1.f and 200.f
	 */
	float mZFar;
	float mZNear;
};

// A Function pointer to a function that will create a IGfxCamera.
#define CAM_FACTORY_FCTN_PTR(var) IGfxCamera* (*var) (float, float)

extern "C"  IGfxCamera* GFX_CREATE_DEFAULT_CAMERA(float inFOV, float inAR);
#endif // _GFXCAMERA_H
