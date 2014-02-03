#pragma once
#ifndef _TEXTURECUBE_H
#define _TEXTURECUBE_H

#include "CommonGfx.h"
#include "ITexture.h"

/*
 * Cube Texture.
 */
class TextureCube: public ITexture {
public:
  friend class TextureManager;

protected:
  TextureCube(void);
  virtual ~TextureCube(void);
  
	/*
	 * Notify when data is modified and should be copied into the texture object.
	 */
  virtual void PreTextureDataLoaded();
	virtual void TextureDataLoaded();
  virtual void PostTextureDataLoaded();

private:

};

#endif // _TEXTURECUBE_H
