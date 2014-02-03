#include "Texture2D.h"

void Texture2D::PreTextureDataLoaded() {
  ITexture::PreTextureDataLoaded();
}

void Texture2D::TextureDataLoaded() {
  ITexture::TextureDataLoaded();
	glTexStorage2D(mBindTarget, 4, GL_RGB8, mTexSizeWidth, mTexSizeHeight);
	glTexSubImage2D(mBindTarget, 0, 0, 0, 
                  mTexSizeWidth, mTexSizeHeight, 
                  GL_RGB, GL_UNSIGNED_BYTE, mTextureData[0]);
}

void Texture2D::PostTextureDataLoaded() {
  ITexture::PostTextureDataLoaded();
}
