#pragma once
#ifndef _MATCONSTANTS_H
#define _MATCONSTANTS_H
#include "CommonShader.h"


const std::string MAT_PARAMETER_SECTION = "..PARAMS";
const int MAT_SECTION_HEADER_LEN = 7;
const std::string GLSL_VERSION_TEXT = "#version 330";
const std::string GLSL_BRDF_PARAM_STRUCT = "BRDF_PARAM_STRUCT";

// LIGHT PARAMETERS
const std::string GLSL_LIGHT_PARAM_STRUCT = "LIGHT_PARAM_STRUCT";

// LIGHT FUNCTIONS (GLSL Strings)
const int POINT_LIGHT_ID = 0;
const int DIR_LIGHT_ID = 1;

const std::string GLSL_LIGHT_PARAM_NAME = "light";
const std::string GLSL_POINT_LIGHT_DISPATCH = ("if (" + GLSL_LIGHT_PARAM_NAME + ".lightId == 0) return POINT_LIGHT_DISPATCH(" + GLSL_LIGHT_PARAM_NAME + ", brdf);\n");
const std::string GLSL_DIR_LIGHT_DISPATCH = ("if (" + GLSL_LIGHT_PARAM_NAME + ".lightId == 1) return DIR_LIGHT_DISPATCH(" + GLSL_LIGHT_PARAM_NAME + ", brdf);\n");

#if BLINN_PHONG_BRDF
const std::string BRDF_NAME = "BlinnPhong";
const std::string BRDF_DIFFUSE = "..DIFFS";
const std::string BRDF_DIFFUSE_VAR = "diffuse";
const int DIFFUSE_SEC_ID = 1;

const std::string BRDF_SPECULAR = "..SPECR";
const std::string BRDF_SPECULAR_VAR = "specular";
const int SPECULAR_SEC_ID = 2;

const std::string BRDF_AMBIENT = "..AMBNT";
const std::string BRDF_AMBIENT_VAR = "ambient";
const int AMBIENT_SEC_ID = 3;

const std::string BRDF_SHININESS = "..SHINI";
const std::string BRDF_SHININESS_VAR = "shininess";
const int SHININESS_SEC_ID = 4;

#endif // BRDF

#endif