#include "IRenderableInstance.h"
#include "IRenderable.h"

IRenderableInstance::IRenderableInstance(IRenderable* inRen, WorldObject* inObj): mParentRenderable(inRen), mParentObject(inObj), mIsRegistered(false), mShaderProgramID(-1) {
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

/* 
 * Render Function.
 */
void IRenderableInstance::OnRender() {
	if (mShaderProgramID != -1) {
		for(SHADER_DATA_ITER_t iterator = mInternalShaderData.begin(); iterator != mInternalShaderData.end(); iterator++) {
			if (iterator->second->mUniform) {
				SetUniformShaderData(iterator->first, iterator->second);
			}
		}

		for(SHADER_DATA_ITER_t iterator = mExternalShaderData.begin(); iterator != mExternalShaderData.end(); iterator++) {
			if (iterator->second->mUniform) {
				SetUniformShaderData(iterator->first, iterator->second);
			}
		}
	}
}

void IRenderableInstance::PrepareRender() {
	glUseProgram(mShaderProgramID);

	PreRender();
}

void IRenderableInstance::FinishRender() {
	PostRender();

	glUseProgram(0);
}

/*
 * Calls the appropriate glUniform* function on the shader.
 */
void IRenderableInstance::SetUniformShaderData(GLint inLoc, SShaderData* inData) {
	switch (inData->mType) {
	case ESDT_MATRIX4x4:
		glUniformMatrix4fv(inLoc, 1, GL_FALSE, glm::value_ptr(*(glm::vec4*)inData->mData));
		break;
	default:
		break;
	}
}