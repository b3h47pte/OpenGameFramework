#pragma once
#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "CommonGfx.h"
#include "CommonShader.h"
#include "MaterialConstants.h"

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

// These are other BRDF properties that should be specified by the material
// and shouldn't necessarily be calculated.
#if BLINN_PHONG_BRDF
struct MaterialBRDFProperties {
  glm::vec4 ambient;
  float shininess;
};
#endif // BRDF

/*
 * Materials determine how a mesh gets rendered (i.e. its diffuse color, specular color, etc.). 
 * The goal is to eventually allow for the creation of complex materials like those that can be made
 *  using the UE3/4 material editor.
 *  
 * General Idea: Each material is linked with the 'base' material that has all the lighting functions. 
 *  This lighting function will be used to determine the effect of various lights on the material. The base
 *  material will declare these subroutines but it will be up to the individual material to define them as
 *  appropriate. The materials then will each implement their own main function that calculates the 
 *  various parameters of the BRDF. It is also important to note that each material shader will each be a "pseudo-shader" that will be 
 *  split into sections:
 *    1) Material Parameters. Uniforms that the material needs.
 *    2) Function Body. Pseudo-GLSL that will be used as the shader. This should not include the subroutine/function declaration and the curly braces.
 *        There will be a number of function bodies as specified by the BRDF model being used.
 *    
 *  It is important to note that the version of GLSL that is used is not determined by the material, but by the engine.
 *  It could be interesting, in the future, to make it configurable.
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
  void GenerateShaderSource();

  void ParseParameter(const std::string& param);
  std::map<std::string, MaterialParam*> ParameterMapping;

  void ParseShaderBodyLine(const std::string& line);
  void ParseEntireShaderBody();
  std::string mMaterialBodyText;

  // Actual GLSL that gets created from the material. 
  std::string mShaderSource;

  // BRDF Properties. These should be defined by the creator of the material.
  MaterialBRDFProperties mBRDFProperties;
};

#endif // _MATERIAL_H