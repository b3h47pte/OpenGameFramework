#include "IRenderableInstance.h"
#include "IRenderable.h"
#include "ITexture.h"

IRenderableInstance::IRenderableInstance(IRenderable* inRen, WorldObject* inObj): 
                                          mParentRenderable(inRen), 
                                          mParentObject(inObj), mIsRegistered(false),
                                          mShaderProgramID(-1) {
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
	PrepareShaderData();
}

/*
 * Set shader data as necessary -- internal/externally set shader data.
 */
void IRenderableInstance::PrepareShaderData() {
	if (mShaderProgramID != -1) {
		mTextureLocationCount = 0;
		for(SHADER_DATA_ITER_t iterator = mInternalShaderData.begin(); 
        iterator != mInternalShaderData.end(); iterator++) {
			if (iterator->second.mUniform) {
				SetUniformShaderData(iterator->first, iterator->second);
			}
		}

		for(SHADER_DATA_ITER_t iterator = mExternalShaderData.begin(); 
        iterator != mExternalShaderData.end(); iterator++) {
			if (iterator->second.mUniform) {
				SetUniformShaderData(iterator->first, iterator->second);
			}
		}
	}
}

void IRenderableInstance::PrepareRender() {
  OGL_CALL(glUseProgram(mShaderProgramID));

  // Model Matrix
  SShaderData modelData;
  modelData.mType = ESDT_MATRIX4x4;
  modelData.mData = &mTransformationMatrix;
  modelData.mUniform = true;

  int modelIndx = GetUniformLocation("model_matrix");
  SetInternalShaderData(modelIndx, modelData);

	PreRender();
}

void IRenderableInstance::FinishRender() {
	PostRender();

  OGL_CALL(glUseProgram(0));
}

/*
 * Calls the appropriate glUniform* function on the shader.
 */
void IRenderableInstance::SetUniformShaderData(GLint inLoc, SShaderData& inData) {
	switch (inData.mType) {
	case ESDT_MATRIX4x4:
    OGL_CALL(glUniformMatrix4fv(inLoc, 1, GL_FALSE,
      glm::value_ptr(*(glm::vec4*)inData.mData)));
		break;
	case ESDT_TEX2D:
  case ESDT_TEXCUBE:
		{
		OGL_CALL(glUseProgram(mShaderProgramID));
    GLint loc = OGL_CALL(glGetUniformLocation(mShaderProgramID, inData.mLocation.c_str()));
    OGL_CALL(glUniform1i(loc, mTextureLocationCount));
    OGL_CALL(glActiveTexture(GL_TEXTURE0 + mTextureLocationCount));
		ITexture* tex = (ITexture*)inData.mData;
		glBindTexture(tex->GetTextureBindTarget(), tex->GetTextureID());
		++mTextureLocationCount;
		}
		break;
	default:
		break;
	}
}
