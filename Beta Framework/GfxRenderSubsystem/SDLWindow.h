#pragma once

#ifndef _SDLWINDOW_H
#define _SDLWINDOW_H

#include "CommonGfx.h"

#ifdef USE_SDL
#include "GfxWindow.h"

#include "SDL.h"

class SDLWindow: public IGfxWindow
{
public:
	SDLWindow(void);
	virtual ~SDLWindow(void);

	/*
	 * Error Handling
	 */
	enum ESDLErrorCodes {
		ESDL_INITFAIL,
		ESDL_SETVIDEOMODE,
	};
	virtual void DumpError(int) const;
private:
	/*
	 * SDL Variables
	 */
	SDL_Surface* mSDLSurface;

	virtual void CreateOpenGLContext();
};

#endif // USE_SDL
#endif // _SDLWINDOW_H 