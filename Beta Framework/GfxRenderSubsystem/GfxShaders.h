#pragma once
#ifndef _GFXSHADERS_H
#define _GFXSHADERS_H

#include "CommonGfx.h"
#include <map>
/*
 * GfxShaders manages all the shaders loaded and this way we can compile/link shaders once instead of compiling/linking a shader once for each mesh object.
 */
class GfxShaders
{
public:
	GfxShaders(void);
	~GfxShaders(void);

  static std::string GetShaderDirectory();
	static int	GetShaderID(GLenum, const std::string&);
	static bool LoadShader(GLenum, const std::string&, const std::string&);

private:
	static std::map<GLenum, std::map<std::string, GLuint> > mShaderStore;
};

#endif // _GFXSHADERS_H
