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
		ESDL_WINDOW,
	};
	virtual void DumpError(int) const;

	/*
	 * Tick
	 */ 
	virtual bool ShouldTick()  { return mStillRunning; }
	virtual void Tick(float);

private:
	/*
	 * Input
	 */ 
	virtual void ProcessKeyboardInputSDL(uint32_t, unsigned int, SDL_Keysym);

	/*
	 * SDL Variables
	 */
	SDL_Window* mSDLWindow;
	SDL_GLContext	mGLContext;

	virtual void CreateOpenGLContext();

	bool mStillRunning;
};

#ifndef NDEBUG
#define SDL_ERROR_CHECK()	CHECK_SDL_ERROR()
#else 
#define	SDL_ERROR_CHECK()	
#endif

inline void CHECK_SDL_ERROR() {
	const char *error = SDL_GetError();
	if (*error != '\0')
	{
		printf("SDL Error: %s\n", error);
		SDL_ClearError();
	}
}

#endif // USE_SDL
#endif // _SDLWINDOW_H 