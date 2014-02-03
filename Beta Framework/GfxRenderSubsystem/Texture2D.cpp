#include "Texture2D.h"

Texture2D::Texture2D() {
}

Texture2D::~Texture2D() {
}

void Texture2D::PreTextureDataLoaded() {
  ITexture::PreTextureDataLoaded();
}

void Texture2D::TextureDataLoaded() {
  ITexture::TextureDataLoaded();
	glTexStorage2D(GetBindTarget(), 4, GL_RGB8, mTexSizeWidth, mTexSizeHeight);
	glTexSubImage2D(GetBindTarget(), 0, 0, 0, 
                  mTexSizeWidth, mTexSizeHeight, 
                  GL_RGB, GL_UNSIGNED_BYTE, mTextureData[0]);
}

void Texture2D::PostTextureDataLoaded() {
  ITexture::PostTextureDataLoaded();
}
