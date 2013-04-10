#include "GfxSubsystem.h"
#include "GfxWindow.h"

#ifdef USE_SDL
#include "SDLWindow.h"
#endif

/* 
 * Factory Function To create the GFx Subsystem. Will return NULL when it fails.
 */
extern "C" GFXSUBAPI IGfxSubsystem* GetGfxSubsystem() {
	// Initialize a GFx Subsystem entirely and make sure it's ready to use right after this function is called
	static GfxSubsystem* newSub = [] () {
		GfxSubsystem* sub = new GfxSubsystem();
		WRAP_ERROR_CHECK_CLEANUP_SETNULL_RETURN(sub);
		return sub;
	}();
	return newSub;
}

GfxSubsystem::GfxSubsystem(void): mStillRunning(true) {
	// Initialize some basic GLEW/OpenGL stuff if we can -- otherwise wait for the user to pass in the context and the like
	if (!glewInit()) {
		SetError(EGLEW_FAIL);
	}

	// Initialize Window
#ifdef USE_SDL
	mWindow = new SDLWindow();
#endif
	WRAP_ERROR_CHECK_CLEANUP_SETERROR(mWindow, EWINDOW_FAIL);
}

GfxSubsystem::~GfxSubsystem(void) {
}

/*
 * Displays the appropriate error message for GfxSubsystem.
 */ 
void GfxSubsystem::DumpError(int inErr) const {
	switch (inErr) {
	case EGLEW_FAIL:
		ERROR_PRINT("GLEW failed to initialize.");
		break;
	case EWINDOW_FAIL:
		ERROR_PRINT("The Window failed to initialize.");
		break;
	default:
		break;
	}
}

/*
 * Tick. Calls tick in the windowing system and in the backend.
 */
void GfxSubsystem::Tick(float inDeltaTime) {
	// handle all pending events
	SDL_Event event;
	while( SDL_PollEvent(&event) )
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mStillRunning = false;
			break;
		default:      
			break;
		}
	}
}