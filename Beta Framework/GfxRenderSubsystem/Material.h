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

/*
 * Materials determine how a mesh gets rendered (i.e. its diffuse color, specular color, etc.). 
 * The goal is to eventually allow for the creation of complex materials like those that can be made
 *  using the UE3/4 material editor.
 *  
 * General Idea: Each material is linked with the 'base' material that has all the lighting functions. 
 *  This lighting function will be used to determine the effect of various lights on the material. The base
 *  material will define these functions based on the BRDF chosen; however, all the other materials must
 *  pass in the BRDF parameters to it.
 *  
 *  The materials then will each implement their own 'main' function that calculates the 
 *  various parameters of the BRDF and outputs a final color. 
 *  
 *  It is also important to note that each material shader will each be a "pseudo-shader" that will be 
 *  split into sections:
 *    1) Material Parameters. Uniforms that the material needs.
 *    2) Function Bodies for each item in the BRDF.
 *        Each function body will return a vec4.
 *    
 *  It is important to note that the version of GLSL that is used is not determined by the material, but by the engine.
 *  It could be interesting, in the future, to make it configurable.
 *       
 * "Pseudo-GLSL": Should be GLSL syntax with a few exceptions where we can present an interface for the material creator to insert
 *    GLSL from an external source. Other than that, the shader code should compile as is.
 *  
 * A dispatch shader will be generated during a pre-process phase which will combine the materials necessary for
 * a renderable (which may have different materials). Then each vertex (which will each have a material ID), will
 * be shaded using the appropriate material by calling the appropriate material function. The dispatch function
 * will set the appropriate 'out' variable that sets the color. 
 */
class Material
{
public:
  Material(std::string& source, std::string& uniqueId);
  virtual ~Material();

  static std::string GenerateShaderParameterName(const std::string& id, const std::string& param);
  static std::string GenerateShaderFunctionName(const std::string& id, const std::string& extra);

protected:
  void CleanupMaterialParam(MaterialParam*);

private:
  std::string mMaterialSource;
  std::string mMaterialId; // Unique ID. If multiple materials are linked to each other that have the same ID, then bad things will happen.
  std::string GetMaterialDirectory() const;
  /*
   * Load material from the file specified by 'mMaterialSource' 
   */
  void LoadMaterial();
  void GenerateShaderSource();
  void CompileShader();

  void ParseParameter(const std::string& param);
  std::map<std::string, MaterialParam*> ParameterMapping;

  void ParseShaderBodyLine(const std::string& line, int section);
  void ParseEntireShaderBody();
  std::map<int, std::string> MaterialBodyMapping;
  std::string ConvertSectionIdToString(int section);

  // Actual GLSL that gets created from the material. 
  std::string mShaderSource;
  int mShaderId;

  // BRDF Properties. These should be defined by the creator of the material.
  bool ParseBRDFSectionHeader(const std::string& header, int& section);
  bool CheckValidBRDFSection(int section);
  std::string GenerateBRDFStructure(const std::string& id, const std::string& name);
  MaterialBRDFProperties mBRDFProperties;
};

#endif // _MATERIAL_H