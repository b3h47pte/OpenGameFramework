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
	TestMessageClient() : mRight(0.f), mForward(0.f), mUp(0.f) { RegisterInitialGroups(); }
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


int _tmain(int argc, _TCHAR* argv[])
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

	MeshRenderable* mesh = new MeshRenderable();
	mesh->AddVertex(verts[0], norms[0], tex[0]);
	mesh->AddVertex(verts[1], norms[1], tex[1]);
	mesh->AddVertex(verts[2], norms[2], tex[2]);
	mesh->AddTriangleIndex(0);
	mesh->AddTriangleIndex(1);
	mesh->AddTriangleIndex(2);
	mesh->SetVertexShader("C:/Users/Michael/Documents/GitHub/OpenGameFramework/Beta Framework/GfxRenderSubsystem/Sample Shaders/Basic/basic.vert");
	mesh->SetFragShader("C:/Users/Michael/Documents/GitHub/OpenGameFramework/Beta Framework/GfxRenderSubsystem/Sample Shaders/Basic/basic.frag");
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
