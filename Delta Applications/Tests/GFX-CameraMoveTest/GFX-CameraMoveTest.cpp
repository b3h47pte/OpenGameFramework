// GFX-CameraMoveTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include "GfxSubsystem.h"
#include "MeshRenderable.h"
#include "MessageServer.h"
#include "IMessageClient.h"
#include "ITickable.h"

class TestMessageClient: public GfxCamera, public IMessageClient, public ITickable {
public:
  TestMessageClient() : mRight(0.f), mForward(0.f), mUp(0.f), mTurnLeft(0.f), mTurnUp(0.f) { RegisterInitialGroups(); }
  ~TestMessageClient() {}

  virtual void NotifyKeyInputMessage(const sKeyInputMessageData& in) {
    if (in.mKeyState == INPUT_KEY_DOWN || in.mKeyState == INPUT_KEY_REPEAT) {
      switch (in.mKeyCode) {
      case EKEY_W: // move camera forward
        mForward = 1.f;
        break;
      case EKEY_A: // move camera left
        mRight = -1.f;
        break;
      case EKEY_S: // move camera backwards
        mForward = -1.f;
        break;
      case EKEY_D: // move camera right
        mRight = 1.f;
        break;
      case EKEY_SPACE:
        mUp = 1.f;
        break;
      case EKEY_LEFT_CTRL:
        mUp = -1.f;
        break;
      case EKEY_LEFT:
        mTurnLeft = 1.f;
        break;
      case EKEY_RIGHT:
        mTurnLeft = -1.f;
        break;
      case EKEY_UP:
        mTurnUp = 1.f;
        break;
      case EKEY_DOWN:
        mTurnUp = -1.f;
        break;
      }
      
    } else {
      switch (in.mKeyCode) {
      case EKEY_W: // move camera forward
      case EKEY_S: // move camera backwards
        mForward = 0.f;
        break;
      case EKEY_A: // move camera left
      case EKEY_D: // move camera right
        mRight = 0.f;
        break;
      case EKEY_SPACE:
      case EKEY_LEFT_CTRL:
        mUp = 0.f;
        break;
      case EKEY_LEFT:
      case EKEY_RIGHT:
        mTurnLeft = 0.f;
        break;
      case EKEY_UP:
      case EKEY_DOWN:
        mTurnUp = 0.f;
        break;
      }
    }
  }

  virtual void Tick(float delta) {
    glm::vec4 pos = GetPosition();
    glm::vec4 fdir = GetForwardDirection();
    glm::vec4 rdir = GetRightDirection();
    glm::vec4 udir = GetUpDirection();
    pos += (delta * (fdir * 1.f * mForward + rdir * 1.f * mRight + udir * 1.f * mUp));
    SetPosition(pos);

    glm::mat4 rot = GetRotationMatrix();
    glm::mat4 mat;
    mat = glm::rotate(rot, 0.1f * mTurnLeft, glm::vec3(GetWorldUp()));

    glm::mat4 mat2;
    mat2 = glm::rotate(mat, 0.1f * mTurnUp, glm::vec3(GetWorldRight()));
    SetRotation(mat2);
  }

  virtual bool ShouldTick() { return true; }

protected:
  virtual void RegisterInitialGroups() { 
    GetGlobalMessageServer()->RegisterClient(this, EMG_KEYINPUT); 
  }

private:
  float mRight;
  float mForward;
  float mUp;

  float mTurnLeft;
  float mTurnUp;
};

extern "C"  IGfxCamera* GFX_CREATE_TEST_CAMERA(float inFOV, float inAR) {
  IGfxCamera* cam = [&] () {
    IGfxCamera* newCam = new TestMessageClient();
    if (!newCam) return (IGfxCamera*)NULL;
    newCam->SetFOV(inFOV);
    newCam->SetAspectRatio(inAR);
    return newCam;
  }();
  return cam;
}


int main(int argc, char** argv)
{

  IGfxSubsystem* gfx = GetGfxSubsystem(GFX_CREATE_TEST_CAMERA);
  MessageServer* srv = GetGlobalMessageServer();
  if (!gfx)
    return 0;
  
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
    {0.f, 0.f},
    {0.f, 0.f}
  };

  const GLubyte* strVersion = glGetString (GL_VERSION);   
  std::cout << strVersion << std::endl;

  MeshRenderable* mesh = new MeshRenderable();
  mesh->AddVertex(verts[0], norms[0], tex[0]);
  mesh->AddVertex(verts[1], norms[1], tex[1]);
  mesh->AddVertex(verts[2], norms[2], tex[2]);
  mesh->AddTriangleIndex(0);
  mesh->AddTriangleIndex(1);
  mesh->AddTriangleIndex(2);
  mesh->FinalizeData();
  mesh->CreateAndRegisterInstance(NULL);

  while(gfx->ShouldTick()) {
    gfx->Tick(0.1f);
    srv->Tick(0.1f);
    ((TestMessageClient*)gfx->GetViewport(0)->GetCamera())->Tick(0.1f);
    Sleep(1);
  }

  return 0;
}

