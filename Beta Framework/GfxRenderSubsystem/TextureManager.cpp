#include "TextureManager.h"
#include "ITexture.h"
#include "Texture2D.h"
#include "TextureCube.h"

TextureManager* GetTextureManager() {
	static TextureManager* mng = [] (){
		TextureManager* tm = new TextureManager();
		return tm;
	}();
	return mng;
}

TextureManager::TextureManager(void): 
  mTextureInvalidationTime(DEFAULT_TEXTURE_INVALID_TIME) {
}


TextureManager::~TextureManager(void) {
}

/*
 * Go through and check to make sure all textures are stil relevant and needed.
 */
void TextureManager::Tick(float delta) {
	clock_t time = clock();
	for (auto it = mAllTextures.cbegin(); it != mAllTextures.cend(); ) {
		// Check if texture is inactive (if it is, erase it)
		if (CheckTextureInvalid(time, (*it).second)) {
			(*it).second->ReleaseResources();
			delete ((*it).second);
			it = mAllTextures.erase(it);
		}
	}
}

/*
 * Determines whether or not a texture should be kept in memory.
 * A texture is put under consideration for invalidation once 'mTextureUseCount'
 * reaches 0. When 'mTextureUseCount' is at 0, it may mean that the texture
 * is no longer being used or that it just has been loaded/used yet. In any case,
 * after a specified amount of time (configurable, most likely?) of idleness,
 * the texture will be removed.
 */
bool TextureManager::CheckTextureInvalid(clock_t curTime, 
                                         class ITexture* inTexture) const {
	if (inTexture->mReleased)
		return true;

	if (inTexture->mTextureUseCount > 0)
		return false;

  clock_t timeElapsed = (curTime - inTexture->mTextureLastTouch) / CLOCKS_PER_SEC;
	if (timeElapsed < mTextureInvalidationTime)
		return false;

	return true;
}

/*
 * Get Texture by checking the map for the ID.
 */
const ITexture* TextureManager::GetTextureConst(const std::string& id) const {
	if (mAllTextures.find(id) != mAllTextures.end())
		return mAllTextures.at(id);
	return NULL;
}

ITexture* TextureManager::GetTexture(const std::string& id) {
	if (mAllTextures.find(id) != mAllTextures.end())
		return mAllTextures.at(id);
	return NULL;
}

ITexture* TextureManager::CreateTexture(const std::string& id, 
                                        ETextureType type, 
                                        ETextureDataType dataType) {

	ITexture* newTex;
	if (type == ETT_2D) {
    newTex = new Texture2D();
		newTex->mBindTarget = GL_TEXTURE_2D;
  } else if (type == ETT_CUBE) {
    newTex = new TextureCube();
    newTex->mBindTarget = GL_TEXTURE_CUBE_MAP;
  } else {
    return NULL; 
  }

	newTex->mTextureType = type;
	newTex->mTextureDataType = dataType;
	return newTex;
}

void TextureManager::SetTextureSpecification(class ITexture* tex, int numTextures, 
                                              int texWidth, int texHeight) {
	tex->mTextureData = CreateTextureArray(tex->mTextureDataType, numTextures);
	tex->mNumTextures = numTextures;
	tex->mTexSizeWidth = texWidth;
	tex->mTexSizeHeight = texHeight;
	tex->KeepAliveTouch();
}

void TextureManager::SetTextureData(class ITexture* tex, int texNum, 
                                    void* texData) {
	size_t dataEleSize = -1;
	tex->mTextureData[texNum] = CreateTextureData(tex->mTextureDataType, 
                                                tex->mTexSizeWidth, 
                                                tex->mTexSizeHeight, dataEleSize);
	if (!tex->mTextureData[texNum]) {
		return;
	}

	memcpy(tex->mTextureData[texNum], 
         texData, 
         dataEleSize * tex->mTexSizeWidth * tex->mTexSizeHeight * 3);
  tex->PreTextureDataLoaded();
	tex->TextureDataLoaded();
  tex->PostTextureDataLoaded();
}

void** TextureManager::CreateTextureArray(ETextureDataType type, int num) {
	switch (type) {
	case ETDT_INT:
		return (void**)new int*[num];
		break;
	case ETDT_BYTE:
		return (void**)new uint8_t*[num];
		break;
	case ETDT_FLOAT:
		return (void**)new float*[num];
		break;
	}
	return NULL;
}

void* TextureManager::CreateTextureData(ETextureDataType type, int width, 
                                        int height, size_t& outSize) {
	int num = width * height * 3;
	switch (type) {
	case ETDT_INT:
		outSize = sizeof(int);
		return (void*)new int[num];
		break;
	case ETDT_BYTE:
		outSize = sizeof(uint8_t);
		return (void*)new uint8_t[num];
		break;
	case ETDT_FLOAT:
		outSize = sizeof(float);
		return (void*)new float[num];
		break;
	}
	return NULL;
}
