#include "GfxCamera.h"

extern "C"  IGfxCamera* GFX_CREATE_DEFAULT_CAMERA(float inFOV, float inAR) {
	IGfxCamera* cam = [&] () {
		IGfxCamera* newCam = new GfxCamera();
		if (!newCam) return (IGfxCamera*)NULL;
		newCam->SetFOV(inFOV);
		newCam->SetAspectRatio(inAR);
		return newCam;
	}();
	return cam;
}

GfxCamera::GfxCamera(void): mZFar(200.f), mZNear(0.5f)
{
}


GfxCamera::~GfxCamera(void)
{
}

/*
 * Construct the view matrix. 
 */
void GfxCamera::UpdateTransformationMatrix() {
  mTransformationMatrix = glm::lookAt(glm::vec3(GetPosition()),
    glm::vec3(GetPosition() + GetForwardDirection()),
    glm::vec3(GetWorldUp()));
}
