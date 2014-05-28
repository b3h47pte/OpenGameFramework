// GFX-CameraMoveTest.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include <iostream>
#include "MeshRenderable.h"
#include "MeshRenderableInstance.h"
#include "../Bootstrap/camera.h"

#ifndef _WIN32
#define Sleep usleep
#include <unistd.h>
#endif

int main(int argc, char** argv)
{

	IGfxSubsystem* gfx = GetGfxSubsystem(GFX_CREATE_TEST_CAMERA);
	MessageServer* srv = GetGlobalMessageServer();
	if (!gfx)
		return 0;

	float cube_vertices[8][4] = {
		// front
		{-1.f, -1.f,  -3.f, 1.f},
		{1.f, -1.f,  -3.f,1.f},
		{1.f,  1.f,  -3.f,1.f},
		{-1.f,  1.f,  -3.f,1.f},
		// back
		{-1.f, -1.f, -1.f,1.f},
		{1.f, -1.f, -1.f,1.f},
		{1.f,  1.f, -1.f,1.f},
		{-1.f,  1.f, -1.f,1.f}
	};

	float norms[3][4] = {
		{0.f, 0.f, 0.f, 0.f},
		{0.f, 0.f, 0.f, 0.f},
		{0.f, 0.f, 0.f, 0.f}
	};

	float tex[3][2] = {
		{0.f, 0.f},
		{0.f, 0.f},
		{0.f, 0.f}
	};
  
  float colors[8][4] = {
    {1.f, 0.f, 0.f, 1.f},
    {0.f, 1.f, 0.f, 1.f},
    {0.f, 0.f, 1.f, 1.f},
    {1.f, 1.f, 0.f, 1.f},
    {1.f, 0.f, 0.f, 1.f},
    {0.f, 1.f, 0.f, 1.f},
    {0.f, 0.f, 1.f, 1.f},
    {1.f, 1.f, 0.f, 1.f}
  };

	const GLubyte* strVersion = glGetString (GL_VERSION); 	
	std::cout << strVersion << std::endl;

	MeshRenderable* mesh = new MeshRenderable();
  size_t colorId = mesh->DeclarePerVertexAttribute(4);

	for (int i = 0; i < 8; ++i) {
		mesh->AddVertex(cube_vertices[i], norms[0], tex[0]);
    mesh->AddPerVertexAttributeData(colorId, colors[i]);
  }

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
	for (int i = 0; i < sizeof(cube_elements) / sizeof(int); ++i) 
		mesh->AddTriangleIndex(cube_elements[i]);

	mesh->FinalizeData();

  // Create 3x3x3 grid of cubes.
  for(int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      for (int z = 0; z <= 2; ++z) {
        IRenderableInstance* m1 = mesh->CreateAndRegisterInstance(NULL);
        m1->MoveRight(i*3.f);
        m1->MoveUp(j*3.f);
        m1->MoveForward(-z*3.f);
      }
    }
  }

	while(gfx->ShouldTick()) {
		gfx->Tick(0.1f);
		srv->Tick(0.1f);
		((TestMessageClient*)gfx->GetViewport(0)->GetCamera())->Tick(0.1f);
		Sleep(1);
	}

	return 0;
}

