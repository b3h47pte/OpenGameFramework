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
	glTexStorage2D(GetBindTarget(), 10, GL_RGB8, mTexSizeWidth, mTexSizeHeight);
  for (int i = 0; i < 6; ++i) {
    GLenum target = GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;
    glTexSubImage2D(target, 0, 0, 0, 
                  mTexSizeWidth, mTexSizeHeight, 
                  GL_RGB, GL_UNSIGNED_BYTE, mTextureData[i]);

  }
}

void TextureCube::PostTextureDataLoaded() {
  ITexture::PostTextureDataLoaded();
}
