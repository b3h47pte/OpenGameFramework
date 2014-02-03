#pragma once
#ifndef _TEXTUREMANAGER_H
#define _TEXTUREMANAGER_H

#include "CommonGfx.h"
#include "ITickable.h"
#include <time.h>


#define DEFAULT_TEXTURE_INVALID_TIME	60		

/*
 * Currently Supported Texture Types.
 */
enum ETextureType {
	ETT_2D,
  ETT_CUBE,
	ETT_UNKNOWN
};

/*
 * Texture Data (Int, Byte, Float). 
 * [Not how the texture is stored but rather 
 * how the program should read the data].
 */
enum ETextureDataType {
	ETDT_INT,
	ETDT_BYTE,
	ETDT_FLOAT
};

/* 
 * Class to manage the allocation/freeing of textures in OpenGL.
 * How to Use (Design):
 *	1) Request the appropriate texture to be created by specifying the 
 *      type of texture you want and its string identifier
 *	2) Pass the ITexture pointer along with texture data/specification 
 *      to the texture manager (TextureManager will interface with ITexture 
 *      to call the appropriate OpenGL commands to allocate memory in VRAM)
 *	3) If a shader needs to use texture data, specify that the uniform 
 *      is texture data and pass the identifier and the shader will
 *		  grab the appropriate data that it needs from the TextureManager.
 *	4) Once no more mesh instances are using the texture and the texture becomes 
 *      'inactive,' the texture mananger will automatically
 *		  delete it.
 * NOTE: In the off-chance that the user requests an ITexture but never 
 * loads data into it, the texture manager will recognize that will make it 
 * inactive and delete it.
 * TODO: Generalize this into a garbage collector?
 */
class TextureManager: public ITickable
{
public:
	TextureManager(void);
	~TextureManager(void);

	virtual void Tick(float);
	virtual bool ShouldTick() { return true; }

	void SetTextureInvalidationTime(clock_t in) { mTextureInvalidationTime = in; }
	clock_t GetTextureInvalidationTime() const { return mTextureInvalidationTime; }

	/*
	 * Create/Get Texture (Step 1).
	 */
	const class ITexture* GetTextureConst(const std::string& id) const;
	class ITexture* GetTexture(const std::string& id);
	class ITexture* CreateTexture(const std::string& id, 
                                ETextureType, ETextureDataType);

	/*
	 * Set Texture Specification (information about the data that'll 
   *  be coming in) and Data. Specifies: Number of textures (1 for single 
   *  textures, n if this is an array, 6 for cube) and size of texture 
   *  (width, height).
	 */
	void SetTextureSpecification(class ITexture*, int, int, int);

	/*
	 * Set Texture Data. Given the texture number (0 for a single texture), 
   * copy over the texture data (using memcpy).
	 */ 
	void SetTextureData(class ITexture*, int, void*);

private:
	/*
	 * Invalidation Time Seconds.
	 */
	clock_t mTextureInvalidationTime;

	/*
	 * Determines whether or not a given texture is inactive.
	 */
	bool CheckTextureInvalid(clock_t, class ITexture*) const;

	/*
	 * All textures mapped by an "identity string." Identity string 
	 * should be provided by the engine/application. 
	 */
	std::map<std::string, class ITexture*> mAllTextures;

	/*
	 * Create Texture Data
	 */
	void**	CreateTextureArray(ETextureDataType, int);
	void*	CreateTextureData(ETextureDataType, int, int, size_t&);

#ifndef GFXUTILITY_FREEIMAGE
	friend class ITexture* CreateTextureFromImage(const std::string&, 
                                                const std::string&);

  friend class ITexture* CreateCubeTextureFromImages(const std::string& id,
                                            const std::string** paths,
                                            int numberOfImages);
#endif //  GFXUTILITY_FREEIMAGE
};

TextureManager* GetTextureManager();

#endif // _TEXTUREMANAGER_H
