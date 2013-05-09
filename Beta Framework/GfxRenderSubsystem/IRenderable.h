#pragma once
#pragma warning( push )
#ifndef _IRENDERABLE_H
#define _IRENDERABLE_H

#include "CommonGfx.h"
#include "IRenderableInstance.h"
#include "GfxShaders.h"

/*
 * A renderable object (interface). 
 * If an object is renderable, it must be registered with the Gfx Subsystem which will handle making sure it gets rendered.
 * However, since we want to keep this as modular as possible, I don't specify in what format the renderable has to store its data so at is very primitive state
 *		I will just be reading in vertices/triangles, normals, various textures/color data via some interface functions and rendering that. 
 * EVENTUALLY, I will probably implement something to take care of animations and the like -- maybe allow for more specifics to make OBJ/FBX data more efficient (not sure how that'd work).
 * IRenderable WILL register itself when created and WILL un-register upon destruction. The programmer however is reponsible for marking the Renderable as being ready to render.
 * NOTE: IRenderable ISN'T an INSTANCE. IRenderableInstances are what ACTUALLY are rendered. IRenderables are registered but instances are registered to the IRenderable and they are what get rendered.
 */
class GFXSUBAPI IRenderable
{
public:
	IRenderable();
	virtual ~IRenderable();

	/*
	 * Prepare to Render and Finish Rendering function notifications.
	 * Bind buffers, compile/link shaders, all that good stuff, unbind buffers.
	 */
	virtual bool PrepareToRender() = 0;
	virtual bool FinishRender() = 0;

	/*
	 * Finalize Data and register data with OpenGL
	 */ 
	virtual void FinalizeData() = 0; 

	/*
	 * Whether or not renderable is prepared to render yet.
	 */
	virtual bool GetIsReadyToRender() { return mDataSet; }

	/*
	 * Give users flexibility to do other stuff when the renderable gets registered. (Called AFTER registration).
	 */
	virtual void OnRegistration();

	/*
	 * Unregister us from the link (backend). Called AFTER deregistration.
	 */
	void UnregisterRenderable();
	virtual void OnDeregistration();

	/*
	 * Creates and Registers an instance of this renderable object.
	 */
	IRenderableInstance* CreateAndRegisterInstance(WorldObject*);

	friend class GfxBackend;

protected:
	/*
	 * Whether or not the renderable's data has been appropriately set yet.
	 */ 
	bool mDataSet;

private:
	/*
	 * Function to create a new renderable instance. Made pure virtual because a renderable will have to know what kind of instance it'll make.
	 */
	virtual IRenderableInstance* CreateRenderableInstance(WorldObject*) = 0;

	/*
	 * A renderable will always be part of the the graphics backend (or at least it should be) so hold its link. 
	 * NOTE: This gives warning C241: 'IRenderable::mBackendLink' : class 'TIntrusiveLink<T>' needs to have dll-interface to be used by clients of class 'IRenderable'
	 * Going to pragma it out because it should not be an issue since the variable is private and no-one outside of this DLL should be touching it
	 */
#pragma warning (disable: 4251)
	/*
	 * Link in the linked list of all renderables.
	 */ 
	TIntrusiveLink<IRenderable> mBackendLink;

	/*
	 * Linked list of all renderable instances. 
	 */
	TIntrusiveLinkedList<IRenderableInstance, offsetof(IRenderableInstance, mInstanceLink)> mInstanceList;
#pragma warning (pop)

	/*
	 * Whether or not this renderable has already been registered by the backend.
	 * NEVER CHANGE THIS VARIABLE WITHIN IRENDERABLE -- aside from the unregister function.
	 */
	bool mIsRegistered;
};


#endif // _IRENDERABLE_H