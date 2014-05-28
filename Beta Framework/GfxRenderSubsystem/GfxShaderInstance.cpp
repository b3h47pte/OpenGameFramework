#include "GfxShaderInstance.h"
#include "CommonGfx.h"

GfxShaderInstance::GfxShaderInstance(int VertexId, int FragId) {
  if (VertexId == -1 || FragId == -1) {
    std::cerr << "Attempting to create a GLSL Shader program using invalid vertex/frag shaders." << std::endl;
    return;
  }

  ShaderProgramId = OGL_CALL(glCreateProgram());
  OGL_CALL(glAttachShader(ShaderProgramId, VertexId));
  OGL_CALL(glAttachShader(ShaderProgramId, FragId));
  OGL_CALL(glLinkProgram(ShaderProgramId));
  OGL_CALL(glDetachShader(ShaderProgramId, VertexId));
  OGL_CALL(glDetachShader(ShaderProgramId, FragId));
}


GfxShaderInstance::~GfxShaderInstance()
{
}
