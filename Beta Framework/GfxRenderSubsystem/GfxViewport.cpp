#include "GfxViewport.h"
#include "GfxCamera.h"

GfxViewport::GfxViewport(int inWidth, int inHeight, int inPosX, int inPosY, int idNum, class IGfxCamera* cam): mWidth(inWidth), 
  mHeight(inHeight), mPosX(inPosX), mPosY(inPosY), mViewportNumber(idNum), mCamera(cam)
{
}


GfxViewport::~GfxViewport(void)
{
  if (mCamera) delete mCamera;
}

void GfxViewport::Resize(int inWidth, int inHeight, int inPosX, int inPosY) {
  mWidth = inWidth;
  mHeight = inHeight;
  mPosX = inPosX;
  mPosY = inPosY;

  mCamera->SetAspectRatio((float)inWidth / inHeight);
}
