#include "GfxCamera.h"

extern "C" GFXSUBAPI IGfxCamera* GFX_CREATE_DEFAULT_CAMERA(float inFOV, float inAR) {
	static IGfxCamera* cam = [&] () {
		IGfxCamera* newCam = new GfxCamera();
		if (!newCam) return (IGfxCamera*)NULL;
		newCam->SetFOV(inFOV);
		newCam->SetAspectRatio(inAR);
		return newCam;
	}();
	return cam;
}

GfxCamera::GfxCamera(void)
{
}


GfxCamera::~GfxCamera(void)
{
}
