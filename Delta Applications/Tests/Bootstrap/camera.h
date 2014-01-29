// Basic Camera Functionality.
#include "GfxSubsystem.h"
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
		pos += (delta * (fdir * 1.f * mForward + rdir * 1.f * 
      mRight + GetWorldUp() * 1.f * mUp));
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


