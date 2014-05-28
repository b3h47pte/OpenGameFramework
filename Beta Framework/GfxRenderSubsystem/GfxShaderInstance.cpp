#include "GfxShaderInstance.h"
#include "CommonGfx.h"
#include "ILight.h"

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

void GfxShaderInstance::SetUniformData(int loc, SShaderData& data) {

}

/************************************************************************/
/* Accessor Functions (Thin Wrapper around OpenGL Calls)                */
/************************************************************************/
int GfxShaderInstance::GetUniformLocation(const char* in) {
  assert(ShaderProgramId != -1);
  int ret = OGL_CALL(glGetUniformLocation(ShaderProgramId, in));
  return ret;
}