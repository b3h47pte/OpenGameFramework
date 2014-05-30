#include "GfxUtility.h"
#include "MeshRenderable.h"
#include "WFile.h"
#include "TextureManager.h"

#include <sstream>
#include <algorithm>
#include <iterator>

#define DEBUG_TO_STDOUT 0

using namespace std;
#ifndef GFXUTILITY_NOOBJ
/*
 * Reads in the OBJ file and creates a MeshRenderable. 
 */
IRenderable* 
GfxReadOBJFile(std::string inFile) {
	static float DEFAULT_TEX_COORD[2] = {0.f, 0.f};
	WFile file(inFile);

	MeshRenderable* newMesh = new MeshRenderable();
	if (!newMesh) return NULL;

	vector<string> allObjText;
	file.ReadAllTextData(allObjText);

	/*
	 * Parse OBJ file data.
	 * Support the following definitions:
	 *		- v, vt, vn
	 *		- f
	 */ 
	int lineNum = 0;
	int vertCount = 0;
	for (auto& s : allObjText) {
		// Each command will be in the format: DEFINITION ### ### ###
		// First extract the definition
		istringstream iss(s);
		vector<string> lineData;
		copy(istream_iterator<string>(iss), istream_iterator<string>(), 
          back_inserter<vector<string> >(lineData));

		if (lineData.size() == 0) 
			continue;

		vector<float*> vertPos;
		vector<float*> vertNorm;
		vector<float*> vertTex;

		// Determine what the definition is and act appropriately
		if (lineData[0][0] == '#')
			continue;

		if (lineData[0].compare("v") == 0) {
			// Vertex Position
			// Only support vertices that supply x, y, z. Anything less is an error. 
      // Anything more will be ignored.
			if (lineData.size() < 4) {
				cout << "ReadOBJFile Error: Input 'v' definition has less than \
                  4 arguments on line: " << lineNum << endl;
				return NULL;
			}
			float p[4] = {atof(lineData[1].c_str()), atof(lineData[2].c_str()), atof(lineData[3].c_str()), 1.f };
			vertPos.push_back(p);
		} else if (lineData[0].compare("vt") == 0) {
			// Vertex Texture Coordinate
			if (lineData.size() < 3) {
				cout << "ReadOBJFile Error: Input 'vt' definition has less than 3 \
                  arguments on line: " << lineNum << endl;
				return NULL;
			}
			float t[2] = {atof(lineData[1].c_str()), atof(lineData[2].c_str())};
			vertTex.push_back(t);
		} else if (lineData[0].compare("vn") == 0) {
			// Vertex Normal
			if (lineData.size() < 4) {
				cout << "ReadOBJFile Error: Input 'vn' definition has less than 4 arguments on line: " << lineNum << endl;
				return NULL; 
			}
			float n[4] = {atof(lineData[1].c_str()), atof(lineData[2].c_str()), atof(lineData[3].c_str()), 0.f };
			vertNorm.push_back(n);
		} else if (lineData[0].compare("f") == 0) { 
			// Face
			// Only triangles are supported. Having polygons will cause an 
      // error to be created and no mesh to be made.
			// All vertices MUST include normal data.
			if (lineData.size() < 4) {
				cout << "ReadOBJFile Error: Input 'f' definition has less than 4\
                 arguments on line: " << lineNum << endl;
				return NULL;
			}
			// Create new vertices in the mesh as we read in the faces (feel free to 
      // use the extra memory here(?) because it'll eventually be cleared anyways)
			// Probably should find an easier/more efficient way to do this without 
      // using so much excessive memory but this will work for now
			for (int i = 1; i <= 3; ++i) {
				size_t firstSlash = lineData[i].find('/');
				size_t secondSlash = lineData[i].find('/', firstSlash + 1);

				// Parse position data
				string sPos = lineData[i].substr(0, firstSlash);
				int pos = atoi(sPos.c_str());
				newMesh->AddVertexPosition(vertPos[pos]);

				// Read in tex data if it exists.
				if (firstSlash + 1 != secondSlash) {
					string sTex = lineData[i].substr(firstSlash + 1, secondSlash);
					int tex = atoi(sTex.c_str());
					newMesh->AddVertexTex(vertTex[tex]);

				} else { // Tex Data does not exist -- Use a default (0, 0) filler
					newMesh->AddVertexTex(DEFAULT_TEX_COORD);
				}

				// Read in normal data
				string sNorm = lineData[i].substr(secondSlash+1);
				int norm = atoi(sNorm.c_str());
				newMesh->AddVertexNormal(vertNorm[norm]);

				newMesh->AddTriangleIndex(vertCount);
				++vertCount;
			}
		}
		// Ignore all other definitions (o, g, etc.) as they are not supported
		++lineNum;
	}

	return newMesh;
}
#endif // GFXUTILITY_NOOBJ

#ifndef GFXUTILITY_NOFREEIMAGE

/* 
 * 1) Create Cube Texture.
 * 2) Load Textures from files.
 * 3) Put images into texture.
 * 4) Return.
 */
class ITexture* CreateCubeTextureFromImages(const std::string& id,
                                            const std::string* paths,
                                            int numberOfImages) {
	TextureManager* tm = GetTextureManager();
	if (!tm) {
		return NULL;
	}

	ITexture* tex = tm->CreateTexture(id, ETT_CUBE, ETDT_BYTE);
	if (!tex) {
		return NULL;
	}

  tm->SetTextureSpecification(tex, numberOfImages);
	for (int i = 0; i < numberOfImages; ++i) {
    unsigned int width, height;
    uint8_t* data = GFXU_FI_LoadByteData(paths[i], width, height);
    tm->SetTextureWidthHeight(tex, i, width, height);
    tm->SetTextureData(tex, i, data);
    delete[] data;
	}
  tm->FinalizeTexture(tex);
	return tex;
}

/*
 * 1) Create Texture
 * 2) Load Data from Image
 * 3) Put image data into texture.
 * 4) Return!
 * NOTE: ONLY SUPPORT JPEG FOR NOW. Other file formats will be added in 
 *  later when I figure out what to do with the alpha channel.
 */
class ITexture* CreateTextureFromImage(const std::string& id, 
                                       const std::string& path) {
	TextureManager* tm = GetTextureManager();
	if (!tm) {
		return NULL;
	}

	ITexture* tex = tm->CreateTexture(id, ETT_2D, ETDT_BYTE);
	if (!tex) {
		return NULL;
	}

  unsigned int width, height;
  uint8_t* data = GFXU_FI_LoadByteData(path, width, height);
  if (data == NULL) {
    delete tex;
    return NULL;
  }
  tm->SetTextureSpecification(tex, 1);
  tm->SetTextureWidthHeight(tex, 0, width, height);
  tm->SetTextureData(tex, 0, data);
  delete[] data;

  tm->FinalizeTexture(tex);
	return tex;
}

uint8_t* GFXU_FI_LoadByteData(const std::string& path, unsigned int& width, unsigned int& height) {
  // Get file extension to determine what kind of image we are loading.
  // Supported: JPEG, PNG, TIFF, TARGA, BMP
  size_t idx = path.find_last_of('.');
  FREE_IMAGE_FORMAT fmt = FIF_UNKNOWN;
  if (idx != string::npos) {
    std::string suffix = path.substr(idx + 1);
    if (suffix == "jpg" || suffix == "jpeg") {
      fmt = FIF_JPEG;
    } /*else if (suffix == "png") {
      fmt = FIF_PNG;
      } else if (suffix == "tiff" || suffix == "tif") {
      fmt = FIF_TIFF;
      } else if (suffix == "tga") {
      fmt = FIF_TARGA;
      } else if (suffix == "bmp") {
      fmt = FIF_BMP;
      } */ else {
      // Non-supported file format.
      std::cout << "CreateTextureFromImage :: Unsupported file format." << std::endl;
      return NULL;
    }
  }
  else {
    // No file format? Don't want to assume anything so error out.
    std::cout << "CreateTextureFromImage :: No file format detected." << std::endl;
    return NULL;
  }
  FIBITMAP* bmp = FreeImage_Load(fmt, path.c_str(), 0);
  if (!bmp) {
    // Error loading up the image.
    std::cout << "CreateTextureFromImage :: Error loading image." << std::endl;
    return NULL;
  }

  // Get details about the image.
  width = FreeImage_GetWidth(bmp);
  height = FreeImage_GetHeight(bmp);

  // Create array that contains all the relevant pixel data for the image.
  size_t outSize;
  uint8_t* data = (uint8_t*)TextureManager::CreateTextureData(ETDT_BYTE, width, height, outSize);
  if (!data) {
    std::cout << "CreateTextureFromImage :: Error creating texture data."
      << std::endl;
    FreeImage_Unload(bmp);
    return NULL;
  }

  RGBQUAD rgb;

#if DEBUG_TO_STDOUT
  std::cout << "P3" << std::endl;
  std::cout << width << " " << height << " " << "255" << std::endl;
#endif

  for (unsigned int x = 0; x < width; ++x) {
    for (unsigned int y = 0; y < height; ++y) {
      FreeImage_GetPixelColor(bmp, x, y, &rgb);
      int idx = x * width * 3 + y * 3;
#if DEBUG_TO_STDOUT
      std::cout << (int)rgb.rgbRed << " " << (int)rgb.rgbGreen << " "
        << (int)rgb.rgbBlue << " ";
#endif
      data[idx] = (int)rgb.rgbRed;
      data[idx + 1] = (int)rgb.rgbGreen;
      data[idx + 2] = (int)rgb.rgbBlue;
    }
#if DEBUG_TO_STDOUT
    std::cout << std::endl;
#endif
  }
  FreeImage_Unload(bmp);
  return data;
}

#endif // GFXUTILITY_FREEIMAGE
