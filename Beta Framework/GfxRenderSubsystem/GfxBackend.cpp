#include "GfxBackend.h"
#include "IRenderable.h"

GfxBackend::GfxBackend(void)
{
}


GfxBackend::~GfxBackend(void)
{
}

/*
 * Tick to render all renderables.
 */
void GfxBackend::Tick(float inDeltaTime) {

}

/*
 * Register Renderable with the backend which will guarantee that an object is only ever registered once and that it will be rendered on screen if necessary.
 */
void GfxBackend::RegisterRenderable(IRenderable* inRenderable) {
	// First make sure the renderable hasn't been registered and then proceed to put the renderable into the right data structure
	if (!inRenderable->mIsRegistered) {
		inRenderable->mIsRegistered = true;
	}

}