#pragma once
#ifndef _GFXWINDOW_H
#define _GFXWINDOW_H

#include "CommonGfx.h"

class IGfxWindow: public ErrorCatch,  public ITickable
{
public:
	IGfxWindow(void);
	virtual ~IGfxWindow(void);

	unsigned int GetWindowHeight() { return mWindowSize.Height; }
	unsigned int GetWindowWidth() { return mWindowSize.Width; }

protected:
	struct SWindowSize {
		unsigned int Width;
		unsigned int Height;

		SWindowSize(): Width(800), Height(600) {
		}
	};
	// TODO: Implement some sort of configuration file system in Core to allow us to read the width/height from user preferences instead of the default value
	SWindowSize mWindowSize;

private:
	virtual void CreateOpenGLContext() = 0;
};

#endif // _GFXWINDOW_H