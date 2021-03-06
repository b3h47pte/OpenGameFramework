// GFX-CameraMoveTest.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include "MeshRenderable.h"
#include "ILight.h"
#include "../Bootstrap/camera.h"
#include "../Bootstrap/cube.h"

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

  ILight* light = new ILight(glm::vec4(0.f, 0.f, 0.f, 1.f));
  RenderLightData rld(glm::vec4(0.8f, 0.8f, 0.8f, 1.f));
  light->SetLightData(rld);
  gfx->RegisterLight(light);

  CreateCube();

  while (gfx->ShouldTick()) {
    gfx->Tick(0.1f);
    srv->Tick(0.1f);
    ((TestMessageClient*)gfx->GetViewport(0)->GetCamera())->Tick(0.1f);
    Sleep(1);
  }

  return 0;
}

