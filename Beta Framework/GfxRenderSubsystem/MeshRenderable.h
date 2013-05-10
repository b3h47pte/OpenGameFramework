#pragma once
#ifndef _MESHRENDERABLE_H
#define _MESHRENDERABLE_H

#include "CommonGfx.h"
#include "IRenderable.h"

/*
 * A Mesh Renderable.
 * A "Mesh" is anything that is made up of triangles in the scene.
 */
class GFXSUBAPI MeshRenderable: public IRenderable
{
public:
	MeshRenderable(void);
	virtual ~MeshRenderable(void);

	/*
	 * Accessor methods for Mesh Data (vertex, triangles, shaders).
	 */
	void AddVertex(float p[4], float n[4], float t[2]);
	void AddTriangleIndex(int i) { mTriangleIndices.push_back(i); }
	glm::vec4 GetVertexPosition(int i) const { return mVertexPosition[i]; }
	glm::vec4 GetVertexNormal(int i) const { return mVertexNormals[i]; }
	glm::vec2 GetVertexTexCoord(int i) const { return mTexCoords[i]; }

	// Name of the shader program -- not going to be used for now but will be useful once I started saving the program binary out to a file
	void SetShaderProgram(const std::string&);
	void SetVertexShader(const std::string&);
	void SetFragShader(const std::string&);

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

private:
	// Mesh Data
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
		// Shader Program Name/ID
		std::string			mShaderProgramName;
		GLuint				mShaderProgramID;

		// File to load Vertex Shader data from
		std::string			mVertexShaderFile;

		// File to load Fragment shader data from
		std::string			mFragShaderFile;

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

	// Shader Matrices
	GLint mProjectionMatrix;
	GLint mModelMatrix;
};

#endif // _MESHRENDERABLE