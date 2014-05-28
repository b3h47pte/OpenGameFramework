#pragma once
#ifndef _GFXSHADERINST_H
#define _GFXSHADERINST_H
#include "CommonGfx.h"
#include "CommonShader.h"

/*
 * A shader instance is equivalent to a shader program. 
 * This class will handle the OpenGL calls to set uniform data and the like.
 * 
 * To create a shader instance we require a vertex and a fragment shader. 
 * Then once we actually go to use the shader, we require two things:
 *  1) Light information (light position, color, etc.).
 *  2) Material information (what we're shading i.e. diffuse, spec, etc.).
 * These two items must match with the corresponding structures in the GLSL shaders.
 */
class GfxShaderInstance
{
public:
  ~GfxShaderInstance();

  static GfxShaderInstance* CreateNewInstance(int VertexId, int FragId) {
    GfxShaderInstance* gfx = new GfxShaderInstance(VertexId, FragId);
    return gfx;
  }
  
  int GetId() const { return ShaderProgramId; }

  // Shader Program Accessor Functions
  int GetUniformLocation(const char* in);

  // Light Information -- Populates the appropriate uniform with the data found in the RenderLightData structure.
  void SetLightData(const struct RenderLightData*);

  // Material Information

  // Other Uniform Information
  void SetUniformData(int loc, SShaderData&);

protected:
  GfxShaderInstance(int, int);

private:
  int ShaderProgramId;
};

#endif // _GFXSHADERINST_H