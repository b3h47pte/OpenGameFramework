#include "Material.h"
#include "Texture2D.h"
#include "WFile.h"
#include "GfxUtility.h"
#include "MaterialConstants.h"

#define PARAM_SEC_ID      0
#define BODY_SEC_ID       2
#define INVALID_SEC_ID    -1

Material::Material(std::string& source): mMaterialSource(source) {
  LoadMaterial();
}


Material::~Material()
{
}

// ToDo: Use a better format along the lines of XML/JSON?
void Material::LoadMaterial() {
  std::string realDirectory = GetMaterialDirectory() + mMaterialSource;
  WFile file(realDirectory);
  std::vector<std::string> data;
  file.ReadAllTextData(data);

  int section = INVALID_SEC_ID;
  for (auto& line : data) {
    size_t nonSpace = line.find_first_not_of(" \n\t");
    if (nonSpace == std::string::npos)
      continue;

    // Go through each line and read in PARAM and FUNCTION BODY data.
    // These sections may be out of order so make sure to identify which section we are in first.
    std::string stripped = line.substr(nonSpace);
    std::string header = stripped.substr(0, MAT_SECTION_HEADER_LEN);
    if (header == MAT_PARAMETER_SECTION) {
      section = PARAM_SEC_ID;
      continue;
    } else if (header == MAT_BODY_SECTION) {
      section = BODY_SEC_ID;
      continue;
    }

    switch (section) {
    case PARAM_SEC_ID:
      ParseParameter(stripped);
      break;
    case BODY_SEC_ID:
      ParseShaderBodyLine(stripped);
      break;
    default:
      continue;
      break;
    }
  }
}

/*
 * Exposes a parameter that can be passed to the shader via uniform variables. 
 * Expected format: VARIABLE_TYPE VARIABLE_NAME DEFAULT_VALUE
 * Variable Types: Vec4/Color (Synonymous, distinction is for the end-user), Texture2d, Float.
 * THIS IS CASE SENSITIVE.
 */
void Material::ParseParameter(const std::string& param) {
  size_t split = param.find_first_of(" ");
  if (split == std::string::npos) {
    std::cerr << "Invalid parameter (" << param << ") in material: " << mMaterialSource << std::endl;
    return;
  }

  // Read in the variable type and initialize the parameter and the type/data variables accordingly.
  MaterialParam* newParam = new MaterialParam();
  std::string varType = param.substr(0, split);
  if (varType == "Vec4" || varType == "Color") {
    newParam->paramType = (varType == "Vec4") ? EMPT_VEC4 : EMPT_COLOR;
    newParam->data = (void*)new glm::vec4();
  } else if (varType == "Texture2d") {
    newParam->paramType = EMPT_TEXTURE2D;
    newParam->data = NULL; // TODO: Make some sort of default texture that we can use.
  } else if (varType == "Float") {
    newParam->paramType = EMPT_FLOAT;
    newParam->data = (void*)new float();
  } else {
    CleanupMaterialParam(newParam);
    std::cerr << "Invalid variable type (" << varType << ") in material: " << mMaterialSource << std::endl;
    return;
  }

  // Variable name. This variable name must conform to any GLSL requirement otherwise the shader won't compile.
  // However, we won't do any of those checks here.
  size_t oldSplit = split;
  split = param.find_first_of(" ", split + 1);
  if (split == std::string::npos) {
    CleanupMaterialParam(newParam);
    std::cerr << "Invalid parameter (" << param << ") in material: " << mMaterialSource << std::endl;
    return;
  }
  newParam->name = param.substr(oldSplit + 1, split - oldSplit + 1);

  // Default Value. The expected format is as follows.
  // Vec4/Color: X/R_VALUE,Y/G_VALUE,Z/B_VALUE,W/A_VALUE
  // Texture2D: PATH_TO_TEXTURE
  // Float: FLOAT_VALUE
  // IN ALL OF THESE VALUES, NO WHITE SPACE IS ALLOWED.
  std::string defaultValue = param.substr(split + 1);
  defaultValue.replace(defaultValue.begin(), defaultValue.end(), " ", "");
  defaultValue.replace(defaultValue.begin(), defaultValue.end(), "\t", "");
  switch (newParam->paramType) {
  case EMPT_VEC4:
  case EMPT_COLOR:
    try {
      glm::vec4* vec = (glm::vec4*)newParam->data;
      vec->x = std::stof(defaultValue, &split);
      vec->y = std::stof(defaultValue.substr(split + 1), &split);
      vec->z = std::stof(defaultValue.substr(split + 1), &split);
      vec->w = std::stof(defaultValue.substr(split + 1), &split);
    } catch (...) {
      CleanupMaterialParam(newParam);
      std::cerr << "Invalid vector/color default value (" << defaultValue << ") in material: " << mMaterialSource << std::endl;
      return;
    }
    break;
  case EMPT_TEXTURE2D:
    newParam->data = (void*)CreateTextureFromImage(defaultValue,defaultValue);
    if (newParam->data == NULL) {
      CleanupMaterialParam(newParam);
      std::cerr << "Invalid texture default value (" << defaultValue << ") in material: " << mMaterialSource << std::endl;
      return;
    }
    break;
  case EMPT_FLOAT:
    try {
      *(float*)(newParam->data) = std::stof(defaultValue);
    } catch (...) {
      CleanupMaterialParam(newParam);
      std::cerr << "Invalid float default value (" << defaultValue << ") in material: " << mMaterialSource << std::endl;
      return;
    }
    break;
  }

  ParameterMapping[newParam->name] = newParam;
  delete newParam;
}

void Material::ParseShaderBodyLine(const std::string& line) {

}

std::string Material::GetMaterialDirectory() const {
  return "../Shaders/Materials/";
}

/*
 * Deallocates memory properly for the material parameter.
 */
void Material::CleanupMaterialParam(MaterialParam* param) {
  if (param == NULL)
    return;

  delete param;
}