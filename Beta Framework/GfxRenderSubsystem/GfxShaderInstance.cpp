#include "GfxShaderInstance.h"
#include "CommonGfx.h"
#include "ILight.h"
#include "ITexture.h"

GfxShaderInstance::GfxShaderInstance(int VertexId, int FragId) {
  if (VertexId == -1 || FragId == -1) {
    std::cerr << "Attempting to create a GLSL Shader program using invalid vertex/frag shaders." << std::endl;
    return;
  }

  ShaderProgramId = OGL_CALL(glCreateProgram());
  assert(ShaderProgramId != -1);
  OGL_CALL(glAttachShader(ShaderProgramId, VertexId));
  OGL_CALL(glAttachShader(ShaderProgramId, FragId));
  OGL_CALL(glLinkProgram(ShaderProgramId));
  OGL_CALL(glDetachShader(ShaderProgramId, VertexId));
  OGL_CALL(glDetachShader(ShaderProgramId, FragId));
}


GfxShaderInstance::~GfxShaderInstance()
{
}


/*
 * Goes through all possible light properties and sets the data that is associated with it.
 * However, not all lights need the same properties. If the light's shader does not have the property
 * within the light property structure then the property is ignored and not set. 
 */
void GfxShaderInstance::SetLightData(const RenderLightData* data) {
  if (ShaderProgramId == -1) {
    std::cerr << "SetLightData failed since the Shader Program is not valid." << std::endl;
    return;
  }
  OGL_CALL(glUseProgram(ShaderProgramId));
  int ambientLoc = OGL_CALL(glGetUniformLocation(ShaderProgramId, (data->uniformName + "." + data->ambientName).c_str()));
  if (ambientLoc != -1) {
    OGL_CALL(glUniform4fv(ambientLoc, 1, glm::value_ptr(data->ambient)));
  }

  int diffuseLoc = OGL_CALL(glGetUniformLocation(ShaderProgramId, (data->uniformName + "." + data->diffuseName).c_str()));
  if (diffuseLoc != -1) {
    OGL_CALL(glUniform4fv(diffuseLoc, 1, glm::value_ptr(data->diffuse)));
  }

  int positionLoc = OGL_CALL(glGetUniformLocation(ShaderProgramId, (data->uniformName + "." + data->positionName).c_str()));
  if (positionLoc != -1) {
    OGL_CALL(glUniform4fv(positionLoc, 1, glm::value_ptr(data->position)));
  }
}

void GfxShaderInstance::SetUniformData(SShaderData& data) {
  mShaderData[data.mLocation] = data;
}

void GfxShaderInstance::PrepareUniformData() {
  assert(ShaderProgramId != -1);
  OGL_CALL(glUseProgram(ShaderProgramId));

  unsigned int textureCount = 0;
  for (auto& kv : mShaderData) {
    SShaderData* data = &kv.second;
    if (!data->mUniform)
      return;

    int loc = OGL_CALL(glGetUniformLocation(ShaderProgramId, data->mLocation.c_str()));
    if (loc == -1) {
      std::cout << "SetUniformData failed to find uniform location: " << data->mLocation << std::endl;
      return;
    }

    switch (data->mType) {
    case ESDT_MATRIX4x4:
      OGL_CALL(glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(*(glm::mat4*)data->mData)));
      break;
    case ESDT_TEX2D:
    case ESDT_TEXCUBE:
      OGL_CALL(glUniform1i(loc, textureCount));
      OGL_CALL(glActiveTexture(GL_TEXTURE0 + textureCount));
      ITexture* tex = (ITexture*)data->mData;
      OGL_CALL(glBindTexture(tex->GetTextureBindTarget(), tex->GetTextureID()));
      ++textureCount;
      break;
    }
  }
}

/************************************************************************/
/* Accessor Functions (Thin Wrapper around OpenGL Calls)                */
/************************************************************************/
int GfxShaderInstance::GetUniformLocation(const char* in) {
  assert(ShaderProgramId != -1);
  int ret = OGL_CALL(glGetUniformLocation(ShaderProgramId, in));
  return ret;
}