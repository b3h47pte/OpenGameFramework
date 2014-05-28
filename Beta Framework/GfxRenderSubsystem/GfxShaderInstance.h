#pragma once
#ifndef _GFXSHADERINST_H
#define _GFXSHADERINST_H
/*
 * A shader instance is equivalent to a shader program. 
 * This class will handle the OpenGL calls to set uniform data and the like.
 */
class GfxShaderInstance
{
public:
  GfxShaderInstance();
  ~GfxShaderInstance();
};

#endif // _GFXSHADERINST_H