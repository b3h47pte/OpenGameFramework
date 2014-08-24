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
  data.mData = &mTransformationMatrix;
  shader->SetUniformData(data);

  // Temporary BRDF data [while I get materials setup].
  SShaderData brdfAmbient;
  brdfAmbient.mUniform = true;
  brdfAmbient.mType = ESDT_VEC4;
  brdfAmbient.mLocation = "brdf.ambient";
  brdfAmbient.mData = new glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
  shader->SetUniformData(brdfAmbient);

  SShaderData brdfDiffuse;
  brdfDiffuse.mUniform = true;
  brdfDiffuse.mType = ESDT_VEC4;
  brdfDiffuse.mLocation = "brdf.diffuse";
  brdfDiffuse.mData = new glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
  shader->SetUniformData(brdfDiffuse);

  SShaderData brdfSpecular;
  brdfSpecular.mUniform = true;
  brdfSpecular.mType = ESDT_VEC4;
  brdfSpecular.mLocation = "brdf.specular";
  brdfSpecular.mData = new glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
  shader->SetUniformData(brdfSpecular);

  SShaderData brdfShininess;
  brdfShininess.mUniform = true;
  brdfShininess.mType = ESDT_FLOAT;
  brdfShininess.mLocation = "brdf.shininess";
  brdfShininess.mData = new float(20.0f);
  shader->SetUniformData(brdfShininess);
}

void IRenderableInstance::FinishRender(GfxShaderInstance* shader) {
  shader->RemoveUniformData("model_matrix");
  shader->RemoveUniformData("brdf.diffuse");
  shader->RemoveUniformData("brdf.ambient");
  shader->RemoveUniformData("brdf.specular");
  shader->RemoveUniformData("brdf.shininess");
  PostRender();
}