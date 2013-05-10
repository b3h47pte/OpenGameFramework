#pragma once
#pragma warning( push )
#ifndef _IRENDERABLEINSTANCE_H
#define _IRENDERABLEINSTANCE_H

#include "CommonGfx.h"

class GFXSUBAPI IRenderableInstance:public WorldObject
{
public:
	IRenderableInstance(class IRenderable*, WorldObject*);
	virtual ~IRenderableInstance(void);

	/*
	 * Give users flexibility to do other stuff when the renderable gets registered. (Called AFTER registration).
	 */
	virtual void OnRegistration();

	/*
	 * Unregister us from the link (backend). Called AFTER deregistration.
	 */
	void UnregisterRenderableInstance();
	virtual void OnDeregistration();

	friend class IRenderable;
	friend class GfxBackend;
private:
	/*
	 * What is the difference between Parent Renderable and Parent Object?
	 * Parent Renderable -- Parent renderable holds the mesh's data (material, mesh data, etc)
	 * Parent Object -- The object that this renderable instance is attached to (where we get parent orientation/location from)
	 */
	IRenderable*	mParentRenderable;
	WorldObject*	mParentObject;

	/*
	 * Link in the linked list of all renderable instances.
	 * NOTE: This gives warning C241
	 * Going to pragma it out because it should not be an issue since the variable is private and no-one outside of this DLL should be touching it
	 */
#pragma warning (disable: 4251)
	TIntrusiveLink<IRenderableInstance> mInstanceLink;
#pragma warning (pop)
	/*
	 * Whether or not this renderable has already been registered by the backend.
	 * NEVER CHANGE THIS VARIABLE WITHIN IRENDERABLEINSTANCE -- aside from the unregister function.
	 */
	bool mIsRegistered;

	/*
	 * Render function. Called in the Gfx Backend Render loop.
	 */
	virtual void OnRender();

	/*
	 * Overridable Render Functions. PreRender/PostRender can (and should) be overriden. 
	 * Gives user some flexibility in doing some extra stuff before/after this object gets rendered.
	 */
	virtual void PreRender() = 0;
	virtual void PostRender() = 0;
};

#endif // _IRENDERABLEINSTANCE_H
