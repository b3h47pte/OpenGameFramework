#pragma once
#ifndef _GFXSHADERINST_H
#define _GFXSHADERINST_H
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

  // Light Information
  void SetLightData(struct RenderLightData*);

  // Material Information

protected:
  GfxShaderInstance(int, int);

private:
  int ShaderProgramId;
};

#endif // _GFXSHADERINST_H