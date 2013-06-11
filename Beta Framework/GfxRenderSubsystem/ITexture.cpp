#include "ITexture.h"


ITexture::ITexture(void): mReleased(false), mTextureType(ETT_UNKNOWN), mTextureData(NULL),
	mNumTextures(0), mTexSizeWidth(0), mTexSizeHeight(0), mTextureID(0), mTextureUseCount(0), mTextureLastTouch(clock()) {
	glGenTextures(1, &mTextureID);
}


ITexture::~ITexture(void) {
	ReleaseResources();
}

void ITexture::ReleaseResources() {
	if (mReleased)
		return;

	if (glIsTexture(mTextureID))
		glDeleteTextures(1, &mTextureID);

	mReleased = true;
}
