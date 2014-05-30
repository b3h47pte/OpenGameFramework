#include "GfxShaders.h"
#include "WFile.h"

std::map<GLenum, std::map<std::string, GLuint> > GfxShaders::mShaderStore = std::map<GLenum, std::map<std::string, GLuint> >();

GfxShaders::GfxShaders(void)
{
}


GfxShaders::~GfxShaders(void)
{
}

/*
 * Gets the shader ID. Returns -1 if the Shader is not found.
 */
int GfxShaders::GetShaderID(GLenum type, const std::string& id) {
	if (mShaderStore.find(type) != mShaderStore.end()) {
		if (mShaderStore[type].find(id) != mShaderStore[type].end()) {
			return mShaderStore[type][id];
		}
	} 

	return -1;
}

/*
 * Compiles/links the shader and stores the Shader ID for future reference.
 * NOTE: Input shader MUST be NULL terminated.
 */
bool GfxShaders::LoadShader(GLenum type, const std::string& file, const std::string& id) {
	int shaderId;
	if (!(shaderId = glCreateShader(type)))
		return false;

  std::string realFile = GfxShaders::GetShaderDirectory() + file;

	WFile wfile(realFile);
	const char* data = wfile.ReadAllBinaryDataNull();
	if (!data) {
		std::cout << "Load Shader Error: No data read from shader file." << std::endl;
		return false;
	}
  bool ret = PrepareShader(type, data, id, shaderId);
  delete[] data;
  return ret;
}

/*
 * Compiles/links the shader and stores the Shader ID for future reference. 
 * This function takes the text given to it and compiles it.
 * NOTE: Input shader MUST be NULL terminated.
 */
bool GfxShaders::LoadShaderFromText(GLenum type, const std::string& data, const std::string& id) {
  int shaderId;
  if (!(shaderId = glCreateShader(type)))
    return false;
  return PrepareShader(type, data.c_str(), id, shaderId);
}


bool GfxShaders::PrepareShader(GLenum type, const char* data, const std::string& id, int shaderId) {
  OGL_CALL(glShaderSource(shaderId, 1, &data, NULL));
  OGL_CALL(glCompileShader(shaderId));
  int status;
  OGL_CALL(glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status));
  if (status != GL_TRUE) {
    // Spit out error
    char buffer[150];
    glGetShaderInfoLog(shaderId, 150, NULL, buffer);
    std::cout << "Load Shader Error: " << buffer << std::endl;
    return false;
  }
  mShaderStore[type][id] = shaderId;
  return true;
}

// TODO: Make this more accurate...
std::string GfxShaders::GetShaderDirectory() {
  return "../Shaders/";
}
