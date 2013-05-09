#include "GfxSubsystem.h"
#include "GfxWindow.h"

#ifdef USE_SDL
#include "SDLWindow.h"
#endif

#include "GfxBackend.h"

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
	// Initialize Backend
	mBackend = new GfxBackend();

	// Initialize Window
#ifdef USE_SDL
	mWindow = new SDLWindow();
#endif
	WRAP_ERROR_CHECK_CLEANUP_SETERROR(mWindow, EWINDOW_FAIL);

	// Initialize some basic GLEW/OpenGL stuff if we can -- otherwise wait for the user to pass in the context and the like
	GLenum err;
	err = glewInit();
	if (GLEW_OK != err) {
		SetError(EGLEW_FAIL);
	}
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
	// Do Backend rendering first
	if (mBackend->ShouldTick())
		mBackend->Tick(inDeltaTime);

	// Then take care of SDL
	if (mWindow->ShouldTick()) {
		mWindow->Tick(inDeltaTime);
	} else {
		mStillRunning = false;
	}
}

//##########################################
// Backend Communication
//##########################################

/*
 * Register a renderable by passing it to the backend. The backend will take care of the details, there is no need to do any checks here for validity.
 */ 
void GfxSubsystem::RegisterRenderable(IRenderable* inRenderable) {
	mBackend->RegisterRenderable(inRenderable);
}

