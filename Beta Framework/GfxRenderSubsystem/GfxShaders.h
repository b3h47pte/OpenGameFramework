#pragma once
#ifndef _GFXSHADERS_H
#define _GFXSHADERS_H

#include "CommonGfx.h"
#include <map>

// These strings contain the WHOLE text of the shader.
struct SBaseEffectShaderSource {
  std::string vertexSource;
  std::string fragSource;
};

/*
 * GfxShaders manages all the shaders loaded and this way we can compile/link shaders once instead of compiling/linking a shader once for each mesh object.
 */
class GfxShaders
{
public:
  GfxShaders(void);
  ~GfxShaders(void);

  static std::string GetShaderDirectory();
  static int  GetShaderID(GLenum, const std::string&);
  static bool LoadShader(GLenum, const std::string&, const std::string&);
  static bool LoadShaderFromText(GLenum, const std::string&, const std::string&);
  static std::string LoadShaderText(const std::string& fileName);

  // TODO: Do some shader caching goodness.
  // Retrieve the base shader effects source code.
  static std::map<std::string, SBaseEffectShaderSource>* GetBaseEffects();

private:
  static bool PrepareShader(GLenum, const char*, const std::string&, int);
  static std::map<GLenum, std::map<std::string, GLuint> > mShaderStore;

  // Folder where the base shader effects are.
  static std::string OGF_BASE_SHADER_FOLDER;
  // Cache the base effect shaders text (vertex and fragment)
  static std::map<std::string, SBaseEffectShaderSource> mBaseEffectStore;
};

#endif // _GFXSHADERS_H
