#include "ITexture.h"


ITexture::ITexture(void): mTextureType(ETT_UNKNOWN), mTextureData(NULL),
	                        mNumTextures(0), mTexSizeWidth(0), mTexSizeHeight(0), 
                          mReleased(false), mTextureID(0), 
                          mBindTarget(GL_TEXTURE_2D), mTextureUseCount(0), 
                          mTextureLastTouch(clock()) {
  OGL_CALL(glGenTextures(1, &mTextureID));
}


ITexture::~ITexture(void) {
	ReleaseResources();
}

void ITexture::ReleaseResources() {
	if (mReleased)
		return;

	if (glIsTexture(mTextureID))
    OGL_CALL(glDeleteTextures(1, &mTextureID));

	mReleased = true;
}

void ITexture::PreTextureDataLoaded() {
  OGL_CALL(glBindTexture(mBindTarget, mTextureID));
  GLenum err = glGetError();
  if (err != GL_NO_ERROR)
    std::cout << "glBindTexture Error: " << err << std::endl;
}

void ITexture::TextureDataLoaded() {
}

void ITexture::PostTextureDataLoaded() {
  // TODO: Generalize this into settable parameters as well
  OGL_CALL(glTexParameteri(mBindTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  OGL_CALL(glTexParameteri(mBindTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  OGL_CALL(glTexParameteri(mBindTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  OGL_CALL(glTexParameteri(mBindTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
  OGL_CALL(glGenerateMipmap(mBindTarget));
  OGL_CALL(glBindTexture(mBindTarget, 0));
}
