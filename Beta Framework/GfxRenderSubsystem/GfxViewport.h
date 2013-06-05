#pragma once
#ifndef _GFXVIEWPORT_H
#define _GFXVIEWPORT_H

#include "CommonGfx.h"

class IGfxViewport {
public:
	virtual void Resize(int, int, int, int) = 0;

	virtual int GetViewportWidth() const = 0;
	virtual int GetViewportHeight() const = 0;
	virtual void GetViewportPosition(int&, int&) const = 0;

	virtual void SetCamera(class IGfxCamera* cam) = 0;
	virtual class IGfxCamera* GetCamera() = 0;
};

class GfxViewport: public IGfxViewport
{
public:
	GfxViewport(int, int, int, int, int, class IGfxCamera*);
	~GfxViewport(void);

	/*
	 * If we change the number of viewports, I opt to resize an existing viewport instead of deleting and making a new viewport.
	 */
	virtual void Resize(int, int, int, int);

	virtual int GetViewportWidth() const { return mWidth; }
	virtual int GetViewportHeight() const { return mHeight; }
	virtual void GetViewportPosition(int& inX, int& inY) const { inX = mPosX; inY = mHeight - mPosY; }

	/*
	 * Set/Get Camera
	 */
	void SetCamera(class IGfxCamera* cam) { mCamera = cam; }
	class IGfxCamera* GetCamera() { return mCamera; }

private:
	// Size of Viewport (can only be rectangles...if you want other weird shapes then...I dislike you severely :( )
	int mWidth;
	int mHeight; 

	// Position on Screen
	int mPosX;
	int mPosY; // -- (0,0) is the top left of the screen. GetViewportPosition changes it to become the bottom left of the screen.

	// Viewport ID. 
	int mViewportNumber;

	// Camera
	class IGfxCamera* mCamera;
};

#endif // _GFXVIEWPORT_H