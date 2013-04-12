#pragma once
#pragma warning( push )
#ifndef _IRENDERABLEINSTANCE_H
#define _IRENDERABLEINSTANCE_H

#include "CommonGfx.h"

class GFXSUBAPI IRenderableInstance: public ITickable
{
public:
	IRenderableInstance(class IRenderable*);
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
private:
	IRenderable* mParent;
	/*
	 * Link in the linked list of all renderable instances.
	 * NOTE: This gives warning C241
	 * Going to pragma it out because it should not be an issue since the variable is private and no-one outside of this DLL should be touching it
	 */
#pragma warning (disable: 4251)
	TIntrusiveLink<IRenderableInstance> mInstanceLink;

	/*
	 * Whether or not this renderable has already been registered by the backend.
	 * NEVER CHANGE THIS VARIABLE WITHIN IRENDERABLEINSTANCE -- aside from the unregister function.
	 */
	bool mIsRegistered;
};

#endif // _IRENDERABLEINSTANCE_H
#pragma warning (pop)