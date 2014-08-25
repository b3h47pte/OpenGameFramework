#pragma once
#ifndef _CUBE_H
#define _CUBE_H
#include "MeshRenderable.h"

inline MeshRenderable* CreateCube() {
  float cube_vertices[8][4] = {
    // front
    { -1.f, -1.f, -3.f, 1.f },
    { 1.f, -1.f, -3.f, 1.f },
    { 1.f, 1.f, -3.f, 1.f },
    { -1.f, 1.f, -3.f, 1.f },
    // back
    { -1.f, -1.f, -1.f, 1.f },
    { 1.f, -1.f, -1.f, 1.f },
    { 1.f, 1.f, -1.f, 1.f },
    { -1.f, 1.f, -1.f, 1.f }
  };

  float norms[6][4] = {
    { 0.f, 0.f, -1.f, 0.f }, // front
    { 0.f, 1.f, 0.f, 0.f }, // top
    { 0.f, 0.f, 1.f, 0.f }, // back
    { 0.f, -1.f, 0.f, 0.f }, // bottom
    { 1.f, 0.f, 0.f, 0.f }, // left
    { -1.f, 0.f, 0.f, 0.f } // right
  };

  float tex[3][2] = {
    { 0.f, 0.f },
    { 0.f, 0.f },
    { 0.f, 0.f }
  };

  const GLubyte* strVersion = glGetString(GL_VERSION);
  std::cout << strVersion << std::endl;

  int cube_elements[] = {
    // front
    0, 1, 2,
    2, 3, 0,
    // top
    3, 2, 6,
    6, 7, 3,
    // back
    7, 6, 5,
    5, 4, 7,
    // bottom
    4, 5, 1,
    1, 0, 4,
    // left
    4, 0, 3,
    3, 7, 4,
    // right
    1, 5, 6,
    6, 2, 1,
  };

  size_t totalElements = sizeof(cube_elements) / sizeof(int);
  MeshRenderable* mesh = new MeshRenderable();
  for (size_t i = 0; i < totalElements; ++i) {
    int faceIdx = (int)i / 6;
    mesh->AddVertex(cube_vertices[cube_elements[i]], norms[faceIdx], tex[0]);
  }

  for (size_t i = 0; i < totalElements; ++i)
    mesh->AddTriangleIndex(i);

  mesh->FinalizeData();
  mesh->CreateAndRegisterInstance(NULL);
  return mesh;
}

#endif