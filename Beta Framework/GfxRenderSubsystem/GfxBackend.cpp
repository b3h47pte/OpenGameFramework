#include "GfxBackend.h"

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
	Render(inDeltaTime);	
}

/*
 * Render function.
 */ 
void GfxBackend::Render(float inDeltaTime) {
	// Step through all registered renderables and grab their information to render
	IRenderable* curRenderPtr = mRenderableList.GetHeadElement();
	while(curRenderPtr) {
		// Renderable will take care of setting its data up so its children can render
		curRenderPtr->PrepareToRender();

		// For each Renderable, go through its instances and grab their appropriate information so we can draw 
		// everything with the same material and mesh in one go
		IRenderableInstance* curInstPtr = curRenderPtr->mInstanceList.GetHeadElement();

		while (curInstPtr) {
			curInstPtr->OnRender();
			curInstPtr = curRenderPtr->mInstanceList.GetNextElement(curInstPtr);
		}
		
		curRenderPtr = mRenderableList.GetNextElement(curRenderPtr);
	}
}

/*
 * Register Renderable with the backend which will guarantee that an object is only ever registered once and that it will be rendered on screen if necessary.
 */
void GfxBackend::RegisterRenderable(IRenderable* inRenderable) {
	// First make sure the renderable hasn't been registered and then proceed to put the renderable into the right data structure
	if (!inRenderable->mIsRegistered) {
		inRenderable->mIsRegistered = true;

		mRenderableList.AppendElement(inRenderable);
	}

}