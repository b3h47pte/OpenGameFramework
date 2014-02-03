#pragma once
#ifndef _TEXTURE2D_H
#define _TEXTURE2D_H

#include "CommonGfx.h"
#include "ITexture.h"

/*
 * 2D Texture (Single Texture).
 */
class Texture2D: public ITexture {
public:
  friend class TextureManager;

protected:
  Texture2D(void);
  virtual ~Texture2D(void);

 	/*
	 * Notify when data is modified and should be copied into the texture object.
	 */
  virtual void PreTextureDataLoaded();
	virtual void TextureDataLoaded();
  virtual void PostTextureDataLoaded();

 
private:

};

#endif // _TEXTURE2D_H
