#include "ITexture.h"


ITexture::ITexture(void): mTextureType(ETT_UNKNOWN), mTextureData(NULL),
	                        mNumTextures(0), mTexSizeWidth(0), mTexSizeHeight(0), 
                          mReleased(false), mTextureID(0), 
                          mBindTarget(GL_TEXTURE_2D), mTextureUseCount(0), 
                          mTextureLastTouch(clock()) {
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

void ITexture::PreTextureDataLoaded() {
	glBindTexture(mBindTarget, mTextureID);
}

void ITexture::TextureDataLoaded() {
}

void ITexture::PostTextureDataLoaded() {
  // TODO: Generalize this into settable parameters as well
	glTexParameteri(mBindTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(mBindTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(mBindTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(mBindTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glGenerateMipmap(mBindTarget);
}
