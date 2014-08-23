#pragma once
#ifndef _COMMONSHADER_H
#define _COMMONSHADER_H

enum EShaderDataType {
  ESDT_MATRIX4x4,      // Assumes data comes in as glm::mat4
  ESDT_TEX2D,
  ESDT_TEXCUBE,
  ESDT_FLOAT,
  ESDT_VEC4
};

struct SShaderData {
  bool mUniform;
  void* mData;
  std::string mLocation;
  EShaderDataType mType;
};

#define BLINN_PHONG_BRDF 1

#endif // _COMMONSHADER_H