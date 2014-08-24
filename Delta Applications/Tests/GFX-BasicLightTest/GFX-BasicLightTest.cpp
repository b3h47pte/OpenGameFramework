// GFX-CameraMoveTest.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include "MeshRenderable.h"
#include "ILight.h"
#include "../Bootstrap/camera.h"

#ifndef _WIN32
#include <unistd.h>
#define Sleep usleep
#endif

int main(int argc, char** argv)
{

  IGfxSubsystem* gfx = GetGfxSubsystem(GFX_CREATE_TEST_CAMERA);
  MessageServer* srv = GetGlobalMessageServer();
  if (!gfx)
    return 0;

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

  ILight* light = new ILight(glm::vec4(0.f, 0.f, 0.f, 1.f));
  RenderLightData rld(glm::vec4(0.8f, 0.8f, 0.8f, 1.f));
  light->SetLightData(rld);
  gfx->RegisterLight(light);

  while (gfx->ShouldTick()) {
    gfx->Tick(0.1f);
    srv->Tick(0.1f);
    ((TestMessageClient*)gfx->GetViewport(0)->GetCamera())->Tick(0.1f);
    Sleep(1);
  }

  return 0;
}

