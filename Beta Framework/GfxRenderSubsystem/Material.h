#pragma once
#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "CommonGfx.h"

enum EMaterialParamType {
  EMPT_VEC4,
  EMPT_COLOR,
  EMPT_TEXTURE2D,
  EMPT_FLOAT
};

struct MaterialParam {
  std::string name;
  EMaterialParamType paramType;
  void* data;
};

/*
 * Materials determine how a mesh gets rendered (i.e. its diffuse color, specular color, etc.). 
 * The goal is to eventually allow for the creation of complex materials like those that can be made
 *  using the UE3/4 material editor.
 *  
 * General Idea: Each material is linked with the 'base' material that has all the lighting functions. 
 *  This lighting function will be used to determine the effect of various lights on the material. The base
 *  material will declare these subroutines but it will be up to the individual material to define them as
 *  appropriate. The materials then will each implement their own main function that calculates the appropriate
 *  color. It is also important to note that each material shader will each be a "pseudo-shader" that will be 
 *  split into three sections:
 *    1) Material Parameters. Uniforms that the material needs.
 *    2) Function Body. Pseudo-GLSL that will be used as the shader. 
 *       
 * "Pseudo-GLSL": Should be GLSL syntax with a few exceptions where we can present an interface for the material creator to insert
 *    GLSL from an external source. Other than that, the shader code should compile as is.
 *  
 * A dispatch shader will be generated during a pre-process phase which will combine the materials necessary for
 * a renderable (which may have different materials). Then each vertex (which will each have a material ID), will
 * be shaded using the appropriate material by calling the appropriate material function. 
 */
class Material
{
public:
  Material(std::string& source);
  virtual ~Material();

protected:
  void CleanupMaterialParam(MaterialParam*);

private:
  std::string mMaterialSource;
  std::string GetMaterialDirectory() const;
  /*
   * Load material from the file specified by 'mMaterialSource' 
   */
  void LoadMaterial();

  void ParseParameter(const std::string& param);
  std::map<std::string, MaterialParam*> ParameterMapping;

  void ParseShaderBodyLine(const std::string& line);
};

#endif // _MATERIAL_H