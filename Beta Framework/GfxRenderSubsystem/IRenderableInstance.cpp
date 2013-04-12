#include "IRenderableInstance.h"
#include "IRenderable.h"

IRenderableInstance::IRenderableInstance(IRenderable* inRen): mParent(inRen), mIsRegistered(false) {
}


IRenderableInstance::~IRenderableInstance(void) {
	UnregisterRenderableInstance();
}

/*
 * Unregister the renderable from the backend. We can access the linked list via our link.
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