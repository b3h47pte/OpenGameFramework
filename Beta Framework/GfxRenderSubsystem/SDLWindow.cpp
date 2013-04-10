#include "SDLWindow.h"


SDLWindow::SDLWindow(void) {
	CreateOpenGLContext();
}


SDLWindow::~SDLWindow(void) {
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

	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 32 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1);

	// Create SDL Surface and allow the use of OpenGL
	if ((mSDLSurface = SDL_SetVideoMode(mWindowSize.Width, mWindowSize.Height, 32, SDL_HWSURFACE | SDL_OPENGL)) == NULL) {
		SetError(ESDL_SETVIDEOMODE);
		SDL_Quit();
		return;
	}

	// At this point, we can return and allow the graphics subsystem to continue on and initialize OpenGL
}

/*
 * Displays the right error message when using SDL to create a window.
 */
void SDLWindow::DumpError(int inErr) const {
	switch (inErr) {
	case ESDL_INITFAIL:
		ERROR_PRINT("SDL Failed to initialize.");
		break;
	case ESDL_SETVIDEOMODE:
		ERROR_PRINT("Call to SDL_SetVideoMode failed.");
		break;
	default:
		break;
	}
}