// GfxRenderExample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include "GfxSubsystem.h"
#include "MeshRenderable.h"
#include "MeshRenderableInstance.h"
#include "TextureManager.h"
#include "ITexture.h"
#include "GfxUtility.h"
#include "CommonShader.h"

int main(int argc, char** argv)
{
  
  IGfxSubsystem* gfx = GetGfxSubsystem(GFX_CREATE_DEFAULT_CAMERA);
  if (!gfx)
    return 0;
  TextureManager* texMan = GetTextureManager();
  if (!texMan)
    return 0;
  ITexture* texture = CreateTextureFromImage("test", "Textures/grass.jpg");
  
  float verts[3][4] = {
    {-1.f, -1.f, -2.f, 1.f},
    {1.f, -1.f, -2.f, 1.f},
    {-1.f, 1.f, -2.f, 1.f}
  };

  float norms[3][4] = {
    {-0.90f, -0.90f, 0.f, 0.f},
    {0.85f, -0.90f, 0.f, 0.f},
    {-0.90f, 0.85f, 0.f, 0.f}
  };

  float tex[3][2] = {
    {0.f, 0.f},
    {1.0f, 0.0f},
    {0.f, 1.0f}
  };

  SShaderData texData;
  texData.mData = texture;
  texData.mType = ESDT_TEX2D;
  texData.mUniform = true;
  texData.mLocation = "tex";

  MeshRenderable* mesh = new MeshRenderable();
  mesh->AddVertex(verts[0], norms[0], tex[0]);
  mesh->AddVertex(verts[1], norms[1], tex[1]);
  mesh->AddVertex(verts[2], norms[2], tex[2]);
  mesh->AddTriangleIndex(0);
  mesh->AddTriangleIndex(1);
  mesh->AddTriangleIndex(2);
  mesh->FinalizeData();
  IRenderableInstance* inst = mesh->CreateAndRegisterInstance(NULL);
//  inst->SetExternalShaderData(0, texData);

  while(gfx->ShouldTick()) {
    gfx->Tick(0.1f);
    Sleep(1);
  }

  return 0;
}

