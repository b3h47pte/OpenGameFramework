#include "GfxSubsystem.h"
#include "GfxWindow.h"

#ifdef USE_SDL
#include "SDLWindow.h"
#endif

#include "GfxBackend.h"
#include "GfxViewport.h"
#include "GfxCamera.h"

#include<algorithm>

/* 
 * Factory Function To create the GFx Subsystem. Will return NULL when it fails.
 */
extern "C"  IGfxSubsystem* GetGfxSubsystem(CAM_FACTORY_FCTN_PTR(camptr)) {
	// Initialize a GFx Subsystem entirely and make sure it's ready to use right after this function is called
	static GfxSubsystem* newSub = [&] () {
		GfxSubsystem* sub = new GfxSubsystem(camptr);
		WRAP_ERROR_CHECK_CLEANUP_SETNULL_RETURN(sub);
		return sub;
	}();
	return newSub;
}

GfxSubsystem::GfxSubsystem(CAM_FACTORY_FCTN_PTR(camptr)): mStillRunning(true), mActiveViewports(1), mCameraFactoryFunc(camptr) {
	// Initialize Backend
	mBackend = new GfxBackend();

	// Initialize Window
#ifdef USE_SDL
	mWindow = new SDLWindow();
#endif
	WRAP_ERROR_CHECK_CLEANUP_SETERROR(mWindow, EWINDOW_FAIL);

	// Create Default Viewport
	mAllViewports[0] = new GfxViewport(mWindow->GetWindowWidth(), mWindow->GetWindowHeight(), 0, 0, 0, camptr(90.f,
		(float) mWindow->GetWindowWidth()/ mWindow->GetWindowHeight()));
	for (int i = 1; i < GFX_MAX_VIEWPORTS; i++)
		mAllViewports[i] = NULL;


	// OpenGL initialization
	if(!mBackend->InitializeGraphicsAPI(mWindow->GetWindowWidth(), mWindow->GetWindowHeight())) {
		SetError(EGAPI_FAIL);
	}
}

GfxSubsystem::~GfxSubsystem(void) {
}

/*
 * Displays the appropriate error message for GfxSubsystem.
 */ 
void GfxSubsystem::DumpError(int inErr) const {
	switch (inErr) {
	case EGAPI_FAIL:
		ERROR_PRINT("Graphics API failed to initialize.");
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
	if (mBackend->ShouldTick()) {
		// Go through and render each viewport
		mBackend->PreTick();
		for (int i = 0; i < mActiveViewports; i++) {
			mBackend->SetActiveViewport(mAllViewports[i]);
			mBackend->Tick(inDeltaTime);
		}
	}
	
	// Then take care of SDL
	if (mWindow->ShouldTick()) {
		mWindow->Tick(inDeltaTime);
	} else {
		mStillRunning = false;
	}
	
}

//##########################################
// Viewport
//##########################################
int GfxSubsystem::SetViewportNumber(int inView) {
	mActiveViewports = std::max(std::min(inView, GFX_MAX_VIEWPORTS), 1);

	// Size of each viewport
	// TODO: Let user specify how viewports get split?
	// TODO: Make this more elegant
	// 1 -- Whole Screen
	// 2 -- Split Vertically
	// 3 -- P1 gets top, P2 P3 gets bottom split
	// 4 -- Each player gets a corner
	switch (mActiveViewports) {
	case 1:
		mAllViewports[0]->Resize(mWindow->GetWindowWidth(), mWindow->GetWindowHeight(), 0, 0);
		break;
	case 2:
	case 3:
		mAllViewports[0]->Resize(mWindow->GetWindowWidth(), mWindow->GetWindowHeight() / 2, 0, mWindow->GetWindowHeight() / 2);
		break;
	case 4:
		mAllViewports[0]->Resize(mWindow->GetWindowWidth() / 2, mWindow->GetWindowHeight() / 2, 0, mWindow->GetWindowHeight() / 2);
		break;
	}

	int width;
	int height;
	for (int i = 1; i < mActiveViewports; i++) {
		if (mAllViewports[i] == NULL) {
			switch (mActiveViewports) {
			case 2:
				width = mWindow->GetWindowWidth();
				height = mWindow->GetWindowHeight() / 2;
				mAllViewports[i] = new GfxViewport(mWindow->GetWindowWidth(), mWindow->GetWindowHeight() / 2, 0, 0, i,
					mCameraFactoryFunc(90.f, (float)width/ height));
				break;
			case 3:
				width = mWindow->GetWindowWidth() / 2;
				height = mWindow->GetWindowHeight() / 2;
				mAllViewports[i] = new GfxViewport(mWindow->GetWindowWidth() / 2, mWindow->GetWindowHeight() / 2, 
					(i % 2 == 0) ? 0 : mWindow->GetWindowWidth() / 2, 
					0, i,
					mCameraFactoryFunc(90.f, (float)width/ height));
				break;
			case 4:
				width = mWindow->GetWindowWidth() / 2;
				height = mWindow->GetWindowHeight() / 2;
				mAllViewports[i] = new GfxViewport(mWindow->GetWindowWidth() / 2, mWindow->GetWindowHeight() / 2, 
					(i % 2 == 0) ? 0 : mWindow->GetWindowWidth() / 2, 
					((i / 2) % 2 == 0) ? mWindow->GetWindowHeight() / 2 : 0, i,
					mCameraFactoryFunc(90.f, (float)width/ height));
				break;
			}
		}
	}

	for (int i = mActiveViewports; i < GFX_MAX_VIEWPORTS; i++) {
		if (mAllViewports[i] != NULL) {
			delete mAllViewports[i];
			mAllViewports[i] = NULL;
		}
	}

	return mActiveViewports;
}

class IGfxViewport* GfxSubsystem::GetViewport(int inView) {
	return mAllViewports[inView];
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

