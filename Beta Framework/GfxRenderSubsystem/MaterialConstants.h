#pragma once
#ifndef _MATCONSTANTS_H
#define _MATCONSTANTS_H
#include "CommonShader.h"


const std::string MAT_PARAMETER_SECTION = "..PARAMS";
const std::string MAT_BODY_SECTION = "..FBODY";
const int MAT_SECTION_HEADER_LEN = 7;

#if BLINN_PHONG_BRDF
const std::string BRDF_DIFFUSE = "..DIFFS";
const std::string BRDF_SPECULAR = "..SPECR";
#endif // BRDF

#endif