#pragma once
#ifndef _ITEXTURE_H
#define _ITEXTURE_H

#include "CommonGfx.h"
#include "TextureManager.h"
#include <time.h>

/*
 * Basic Texture Information.
 */
class ITexture
{
public:
	friend class TextureManager;

	GLuint GetTextureID() const { return mTextureID; }
	unsigned int GetTextureBindTarget() const { return mBindTarget; }

	/*
	 * Release Resources (will be called by destructor but can manually call this just in case).
	 */
	void ReleaseResources();

	void KeepAliveTouch() { mTextureLastTouch = clock(); }
protected:
	ITexture(void);
	virtual ~ITexture(void);


	clock_t GetTextureLastTouchTime() const { return mTextureLastTouch; }

	ETextureType	mTextureType;

	ETextureDataType	mTextureDataType;
	void**				mTextureData;
	int					mNumTextures;
	int					mTexSizeWidth;
	int					mTexSizeHeight;

	/*
	 * Notify when data is modified and should be copied into the texture object.
	 */
  virtual void PreTextureDataLoaded();
	virtual void TextureDataLoaded();
  virtual void PostTextureDataLoaded();

  // Getters for subclasses.
  unsigned int GetBindTarget() const { return mBindTarget; }

private:
	bool mReleased;
	/* 
	 * A texture should really only be bound to one texture object (I hope?).
	 */
	GLuint			mTextureID;
	unsigned int	mBindTarget;

	/*
	 * Number of materials currently using this texture.
	 * Once this reaches 0, the texture manager will free 
	 * it from memory once it becomes in-active for a 
	 * period of time.
	 */ 
	unsigned int	mTextureUseCount;

	/*
	 * Time the texture was last used/touched. Tracked so the 
	 * texture manager is able to determine when the 
	 * texture is no longer being used.
	 */
	clock_t			mTextureLastTouch;
};

#endif // _ITEXTURE_H
