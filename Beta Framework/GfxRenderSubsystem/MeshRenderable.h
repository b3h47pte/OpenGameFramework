#pragma once
#ifndef _MESHRENDERABLE_H
#define _MESHRENDERABLE_H

#include "CommonGfx.h"
#include "IRenderable.h"

/*
 * A Mesh Renderable.
 * A "Mesh" is anything that is made up of triangles in the scene.
 */
class  MeshRenderable: public IRenderable
{
public:
	MeshRenderable(void);
	virtual ~MeshRenderable(void);

	/*
	 * Accessor methods for Mesh Data (vertex, triangles, shaders).
	 */
	void AddVertex(float p[4], float n[4], float t[2]);
	void AddTriangleIndex(int i) { mTriangleIndices.push_back(i); }
	void AddVertexPosition(float p[4]);
	void AddVertexNormal(float n[4]);
	void AddVertexTex(float t[2]);
	glm::vec4 GetVertexPosition(int i) const { return mVertexPosition[i]; }
	glm::vec4 GetVertexNormal(int i) const { return mVertexNormals[i]; }
	glm::vec2 GetVertexTexCoord(int i) const { return mTexCoords[i]; }

  /*
   * Provides functionality to specify additional per-vertex attributes
   * aside from the usual vertex location, normals, and texture coordinates.
   */
  struct PerVertexData {
    // Number of components in the vector.
    unsigned int componentCount;
    std::vector<glm::vec4> data;
  };

  // Gets an ID for the new per-vertex attribute that we want to add.
  size_t DeclarePerVertexAttribute(unsigned int componentCount) {
    PerVertexData pvd;
    pvd.componentCount = componentCount;
    mExternalPerVertexAttr.push_back(pvd);
    return mExternalPerVertexAttr.size() - 1;
  }

  // For a per-vertex attribute, add new data.
  // Even though we pass in a glm::vec4, only the first 'componentCount'
  // elements will actually be passed to the shader.
  void AddPerVertexAttributeData(size_t id, float pv[4]) {
    if (id >= mExternalPerVertexAttr.size())
      return;
    mExternalPerVertexAttr[id].data.push_back(glm::vec4(pv[0],
      pv[1], pv[2], pv[3]));
  }

private:
  std::vector<PerVertexData> mExternalPerVertexAttr;
  size_t GetSizeOfExternalVertexAttr() const; 
  void LoadExternalPerVertexAttr(int startIdx, size_t startSize);

public:
	/*
	 * Finalize Data and register data with OpenGL
	 */ 
	virtual void FinalizeData();

	/*
	 * Prepare to Render.
	 * Bind buffers, compile/link shaders, all that good stuff.
	 */
	virtual bool PrepareToRender();
	virtual bool FinishRender();

	// Number of Vertices
	int GetVertexCount() const { return mTriangleIndices.size(); }

private:
	// Mesh Data (These are never cleared).
	struct {
		// Vertex Positions
		std::vector<glm::vec4>		mVertexPosition;

		// Vertex Normals
		std::vector<glm::vec4>		mVertexNormals;

		// Vertex Texture Coordinates
		std::vector<glm::vec2>		mTexCoords;

		// Vertex Indicies
		std::vector<int>			mTriangleIndices;
	};

	// Shader Data
	struct {

		// File to load Vertex Shader data from
		std::string			mVertexShaderFile;
		int	mVertexShaderId;

		// File to load Fragment shader data from
		std::string			mFragShaderFile;
		int mFragShaderId;

	};


	/*
	 * Function to create a new mesh instance.
	 */
	virtual IRenderableInstance* CreateRenderableInstance(WorldObject*);

	/*
	 * OpenGL Variables for Buffers, Shaders.
	 */
	// Element Buffer Object
	GLuint mEBO;

	// Vertex Array Object -- Assuming there's only one per mesh.
	GLuint mVAO;

	// Vertex Buffer Object
	GLuint mVBO;
};

#endif // _MESHRENDERABLE
