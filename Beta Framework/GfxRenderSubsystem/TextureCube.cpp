#include "TextureCube.h"

TextureCube::TextureCube() {
}

TextureCube::~TextureCube() {
}

void TextureCube::PreTextureDataLoaded() {
  ITexture::PreTextureDataLoaded();
}

void TextureCube::TextureDataLoaded() {
  ITexture::TextureDataLoaded();
  OGL_CALL(glTexStorage2D(GetBindTarget(), 3, GL_RGB8, mTexSizeWidth[0], mTexSizeHeight[0]));
  for (int i = 0; i < 6; ++i) {
    assert(mTexSizeWidth[i] == mTexSizeWidth[0] && mTexSizeHeight[i] == mTexSizeWidth[0]);
    GLenum target = GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;
    OGL_CALL(glTexSubImage2D(target, 0, 0, 0,
                  mTexSizeWidth[i], mTexSizeHeight[i], 
                  GL_RGB, GL_UNSIGNED_BYTE, mTextureData[i]));
  }
}

void TextureCube::PostTextureDataLoaded() {
  ITexture::PostTextureDataLoaded();
}
