#include "SDLWindow.h"


SDLWindow::SDLWindow(void): mStillRunning(true) {
	CreateOpenGLContext();
}


SDLWindow::~SDLWindow(void) {
	SDL_GL_DeleteContext(mGLContext);
	SDL_DestroyWindow(mSDLWindow);
}

/*
 * Creates a valid OpenGL context and window using SDL. 
 */ 
void SDLWindow::CreateOpenGLContext() {
	// Make sure we only initialize a subsystem if SDL has been initialized already
	if (SDL_WasInit(SDL_INIT_EVERYTHING) != 0) {
		// SDL is already running so call SDL_InitSubSystem instead
		if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0 ) {
			SetError(ESDL_INITFAIL);
			return;
		}
	}
	else if (SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		SetError(ESDL_INITFAIL);
		return;
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	//SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
 
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Create SDL Window
	mSDLWindow = SDL_CreateWindow("Gfx Backend", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		mWindowSize.Width, mWindowSize.Height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (!mSDLWindow) {
		SetError(ESDL_WINDOW);
		return;
	}
	SDL_ERROR_CHECK();

	// Create OpenGL Context
	mGLContext = SDL_GL_CreateContext(mSDLWindow);
	SDL_ERROR_CHECK();

	// At this point, we can return and allow the graphics subsystem to continue on and initialize OpenGL
	SDL_GL_SetSwapInterval(1);
}

/*
 * Displays the right error message when using SDL to create a window.
 */
void SDLWindow::DumpError(int inErr) const {
	switch (inErr) {
	case ESDL_INITFAIL:
		ERROR_PRINT("SDL Failed to initialize.");
		break;
	case ESDL_WINDOW:
		ERROR_PRINT("Call to SDL_CreateWindow failed.");
		break;
	default:
		break;
	}
}


void SDLWindow::Tick(float inDeltaTime) {
	
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
	
	SDL_GL_SwapWindow(mSDLWindow);
}