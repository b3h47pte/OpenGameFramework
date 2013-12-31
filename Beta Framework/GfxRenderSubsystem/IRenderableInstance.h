#pragma once
#ifndef _IRENDERABLEINSTANCE_H
#define _IRENDERABLEINSTANCE_H

#include "CommonGfx.h"

enum EShaderDataType {
	ESDT_MATRIX4x4,			// Assumes data comes in as glm::mat4
	ESDT_TEX2D
};

struct SShaderData {
	bool mUniform;
	void* mData;
	std::string mLocation;
	EShaderDataType mType;
};

class  IRenderableInstance:public WorldObject
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

	virtual GLuint GetShaderProgram() const { return mShaderProgramID; }
	virtual void SetShaderProgram(GLuint in) { mShaderProgramID = in; }
	GLint GetUniformLocation(const std::string& in) { return glGetUniformLocation(mShaderProgramID, in.c_str()); }
	virtual void SetInternalShaderData(int i, SShaderData* data) { mInternalShaderData[i] = data; }
	virtual void SetExternalShaderData(int i, SShaderData* data) { mExternalShaderData[i] = data; }

	/*
	 * Various Accessor Functions.
	 */
	const IRenderable* GetParentRenderable() const { return mParentRenderable; }

protected:
	/*
	 * Render function. Called in the Gfx Backend Render loop.
	 */
	virtual void OnRender();
	virtual void PrepareRender();
	virtual void FinishRender();

private:
	// Texture Location Count -- 0 to n...will allow us to control which texture unit gets assigned to what sampler in the shader.
	unsigned int mTextureLocationCount;

	/*
	 * Prepares shader data. 
	 */
	virtual void PrepareShaderData();

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
	TIntrusiveLink<IRenderableInstance> mInstanceLink;

	// Uniform Shader Data -- Differentiate between those set internally and those set externally so it can be thread-safe
	std::map<GLint, SShaderData*> mInternalShaderData;
	std::map<GLint, SShaderData*> mExternalShaderData;
	typedef std::map<GLint, SShaderData*>::iterator SHADER_DATA_ITER_t;
	/*
	 * Whether or not this renderable has already been registered by the backend.
	 * NEVER CHANGE THIS VARIABLE WITHIN IRENDERABLEINSTANCE -- aside from the unregister function.
	 */
	bool mIsRegistered;

	/*
	 * Overridable Render Functions. PreRender/PostRender can (and should) be overriden. 
	 * Gives user some flexibility in doing some extra stuff before/after this object gets rendered.
	 */
	virtual void PreRender() = 0;
	virtual void PostRender() = 0;

	// Shader Data -- all renderables have shader data because OpenGL 4 pretty much mandates everything to be drawn with shaders!
	GLuint				mShaderProgramID;

	// Load Uniform/Non-Uniform Data into shader program. 
	// TODO: Do non-uniform data later when I know how it works.
	void SetUniformShaderData(GLint, SShaderData*);
};

#endif // _IRENDERABLEINSTANCE_H
