#pragma once
#ifndef _COMMONSHADER_H
#define _COMMONSHADER_H

enum EShaderDataType {
  ESDT_MATRIX4x4,			// Assumes data comes in as glm::mat4
  ESDT_TEX2D,
  ESDT_TEXCUBE
};

struct SShaderData {
  bool mUniform;
  void* mData;
  std::string mLocation;
  EShaderDataType mType;
};

#endif