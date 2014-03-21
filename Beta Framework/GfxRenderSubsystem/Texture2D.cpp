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
  OGL_CALL(glTexStorage2D(GetBindTarget(), 4, GL_RGB8, mTexSizeWidth[0], mTexSizeHeight[0]));
  OGL_CALL(glTexSubImage2D(GetBindTarget(), 0, 0, 0,
                  mTexSizeWidth[0], mTexSizeHeight[0], 
                  GL_RGB, GL_UNSIGNED_BYTE, mTextureData[0]));
}

void Texture2D::PostTextureDataLoaded() {
  ITexture::PostTextureDataLoaded();
}
