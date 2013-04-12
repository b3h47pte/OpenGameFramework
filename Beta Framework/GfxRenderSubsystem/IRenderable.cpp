#include "IRenderable.h"
#include "GfxSubsystem.h"

/*
 * Ctor/Dtor
 */
IRenderable::IRenderable(): mIsRegistered(false) {
	GetGfxSubsystem()->RegisterRenderable(this);
	OnRegistration();
}

IRenderable::~IRenderable() {
	UnregisterRenderable();
}

/*
 * Create and register and instance for rendering.
 */
IRenderableInstance* IRenderable::CreateAndRegisterInstance() {
	IRenderableInstance* newInst = CreateRenderableInstance();

	if (newInst) {
		mInstanceList.AppendElement(newInst);
		newInst->OnRegistration();
	}

	return newInst;
}

/*
 * Unregister the renderable from the backend. We can access the linked list via our link.
 */
void IRenderable::UnregisterRenderable() {
	if (!mIsRegistered)
		return;

	mBackendLink.Unlink();
	mIsRegistered = false;
	OnDeregistration();
}

/* 
 * Registration Events
 * They do nothing here but can be overridden by child classes.
 */

void IRenderable::OnDeregistration() {

}

void IRenderable::OnRegistration() {

}