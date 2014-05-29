#include "IRenderableInstance.h"
#include "IRenderable.h"
#include "ITexture.h"
#include "GfxShaderInstance.h"

IRenderableInstance::IRenderableInstance(IRenderable* inRen, WorldObject* inObj): 
                                          mParentRenderable(inRen), 
                                          mParentObject(inObj), mIsRegistered(false) {
}


IRenderableInstance::~IRenderableInstance(void) {
	UnregisterRenderableInstance();
}

/*
 * Unregister the renderable from the backend. 
 * We can access the linked list via our link.
 */
void IRenderableInstance::UnregisterRenderableInstance() {
	if (!mIsRegistered)
		return;

	mInstanceLink.Unlink();
	mIsRegistered = false;
	OnDeregistration();
}

/* 
 * Registration Events
 * They do nothing here but can be overridden by child classes.
 */

void IRenderableInstance::OnDeregistration() {

}

void IRenderableInstance::OnRegistration() {

}

/* 
 * Render Function.
 */
void IRenderableInstance::OnRender() {
}

/*
 * Loads the following uniform data into the shader:
 *  1) Model Matrix
 *  2) Material Data.
 */
void IRenderableInstance::PrepareRender(GfxShaderInstance* shader) {
	PreRender();

  // Model Matrix
  SShaderData data;
  data.mUniform = true;
  data.mType = ESDT_MATRIX4x4;
  data.mLocation = "model_matrix";
  shader->SetUniformData(data);


}

void IRenderableInstance::FinishRender() {
	PostRender();
}