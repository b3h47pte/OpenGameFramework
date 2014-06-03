#include "Material.h"
#include "Texture2D.h"
#include "WFile.h"
#include "GfxUtility.h"

#define PARAM_SEC_ID      0
#define INVALID_SEC_ID    -1

Material::Material(std::string& source, std::string& uniqueId): mMaterialSource(source), mMaterialId(uniqueId) {
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

  // Reset to a default state.
  MaterialBodyMapping.clear();
  ParameterMapping.clear();

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
    } else if (ParseBRDFSectionHeader(header, section)) {
      continue;
    }

    switch (section) {
    case PARAM_SEC_ID:
      ParseParameter(stripped);
      break;
    default:
      ParseShaderBodyLine(stripped, section);
      break;
    }
  }

  ParseEntireShaderBody();
  GenerateShaderSource();
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

void Material::ParseShaderBodyLine(const std::string& line, int section) {
  if (!CheckValidBRDFSection(section))
    return;
  // Note: Need to add in the newline just in case there are comments.
  // HOWEVER. I do assume that the #version command (or anything like it) is not in here.
  MaterialBodyMapping[section] += (line + "\n");
}

/*
 * Determine whether or not the input section ID is a valid section for the in-use BRDF.
 */
bool Material::CheckValidBRDFSection(int section) {
#if BLINN_PHONG_BRDF
  return (section == DIFFUSE_SEC_ID) || (section == SPECULAR_SEC_ID);
#endif
}

/*
 * Returns whether or not a new section was found. 
 * If so, sets the section variable accordingly.
 */
bool Material::ParseBRDFSectionHeader(const std::string& header, int& section) {
#if BLINN_PHONG_BRDF
  if (header == BRDF_DIFFUSE)
    section = DIFFUSE_SEC_ID;
  else if (header == BRDF_SPECULAR)
    section = SPECULAR_SEC_ID;
  else
    return false;
  return true;
#endif // BRDF
}

/*
 * Replace OGF Material specific keywords with their appropriate replacements.
 */
void Material::ParseEntireShaderBody() {
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

  if (param->data != NULL) {
    switch (param->paramType) {
    case EMPT_VEC4:
    case EMPT_COLOR:
      delete (glm::vec4*)param->data;
      break;
    case EMPT_TEXTURE2D: // Will eventually be cleaned up by the texture manager.
      break;
    case EMPT_FLOAT:
      delete (float*)param->data;
      break;
    default:
      break;
    }
  }

  delete param;
}

/*
 * Using the data that we have about the function body and the input parameters generate 
 * valid GLSL code that can be used as a fragment shader.
 */
void Material::GenerateShaderSource() {
  mShaderSource = GLSL_VERSION_TEXT + "\n";
  mShaderSource += (BRDF_STRUCT_STRING + "\n");
  mShaderSource += (LIGHT_PARAM_STRUCT_STRING + "\n");

  // Parameters - each of them is a uniform
  for (auto& kv : ParameterMapping) {
    mShaderSource += "uniform ";
    switch (kv.second->paramType) {
    case EMPT_TEXTURE2D:
      mShaderSource += "sampler2D ";
      break;
    case EMPT_VEC4:
    case EMPT_COLOR:
      mShaderSource += "vec4 ";
      break;
    case EMPT_FLOAT:
      mShaderSource += "float ";
      break;
    default:
      break;
    }
    mShaderSource += (GenerateShaderParameterName(mMaterialId, kv.first) + ";\n");
  }

  // Non-Calculated Parameters
  mShaderSource += mBRDFProperties.ToString(mMaterialId);

  // BRDF ELEMENT CALCULATION BODIES
  for (auto& kv : MaterialBodyMapping) {
    mShaderSource += ("vec4 " + GenerateShaderFunctionName(mMaterialId, ConvertSectionIdToString(kv.first)) + "() {\n");
    mShaderSource += kv.second;
    mShaderSource += "}\n";
  }
  
  // MAIN SHADER BODY (This gets automatically generated).
  // Generate a BRDF structure and pass it to the appropriate lighting function as determined by the 'lightId' in the light struct.
  mShaderSource += ("vec4 " + GenerateShaderFunctionName(mMaterialId, "main") + "(" + GLSL_LIGHT_PARAM_STRUCT + " " + GLSL_LIGHT_PARAM_NAME + ") {\n");
  mShaderSource += GenerateBRDFStructure(mMaterialId, "brdf");
  // Light Dispatch..
  mShaderSource += GLSL_POINT_LIGHT_DISPATCH;
  mShaderSource += GLSL_DIR_LIGHT_DISPATCH;
  mShaderSource += "}\n";
}

std::string Material::GenerateBRDFStructure(const std::string& id, const std::string& name) {
  std::string res = (GLSL_BRDF_PARAM_STRUCT + " " + name + ";\n");
#if BLINN_PHONG_BRDF
  res += (name + "." + BRDF_DIFFUSE_VAR + " = " + GenerateShaderFunctionName(id, BRDF_DIFFUSE_VAR) + "\n");
  res += (name + "." + BRDF_SPECULAR_VAR + " = " + GenerateShaderFunctionName(id, BRDF_SPECULAR_VAR) + "\n");
#endif // BRDF
  return res;
}

std::string Material::ConvertSectionIdToString(int section) {
  switch (section) {
#if BLINN_PHONG_BRDF
  case DIFFUSE_SEC_ID:
    return "diffuse";
  case SPECULAR_SEC_ID:
    return "specular";
#endif
  default:
    break;
  }
  return "";
}

std::string Material::GenerateShaderParameterName(const std::string& id, const std::string& param) {
  return (id + "_" + param + "_param");
}

std::string Material::GenerateShaderFunctionName(const std::string& id, const std::string& extra) {
  return (id + "_" + extra + "_call");
}

std::string MaterialBRDFProperties::ToString(const std::string& id) {
  std::string res = "";
#if BLINN_PHONG_BRDF
  res += "uniform vec4 " + Material::GenerateShaderParameterName(id, "ambient") + ";\n";
  res += "uniform float " + Material::GenerateShaderParameterName(id, "shininess") + ";\n";
#endif // BRDF
  return res;
}