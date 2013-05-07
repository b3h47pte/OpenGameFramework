#include "MeshRenderable.h"
#include "MeshRenderableInstance.h"

MeshRenderable::MeshRenderable(void) {
}


MeshRenderable::~MeshRenderable(void) {
}

/*
 * Prepare to Render. -- Calls FinalizeData if the user forgets to do this beforehand.
 * 1) Bind Buffers.
 * 2) Prepare shaders.
 */
bool MeshRenderable::PrepareToRender() {
	if (!mDataSet) {
		FinalizeData();
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBindVertexArray(mVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	return true;
}

/*
 * Finish Rendering by unbinding buffers so that these buffers aren't mistakenly read from/modified.
 */
bool MeshRenderable::FinishRender() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	return true;
}

/*
 * Create a Mesh Renderable Instance for use.
 */
IRenderableInstance* MeshRenderable::CreateRenderableInstance(WorldObject* parObj) {
	IRenderableInstance* newInst = new MeshRenderableInstance(this, parObj);
	return newInst;
}

/*
 * FinalizeData will take the vertex/shader/material data that was input and then create the 
 * necessary OpenGL buffers and shaders and retain information necessary
 * for this renerable to reload the state later for rendering.
 */
void MeshRenderable::FinalizeData() {
	// Create Element Array Buffer (EBO) to hold the indicies of vertices
	glGenBuffers(1, &mEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mTriangleIndices), &mTriangleIndices[0], GL_STATIC_DRAW);

	// Create the VAO to hold the mesh's data (color, position, etc.)
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	// Setup VBO
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mVertexPosition) + sizeof(mVertexNormals) + sizeof(mTexCoords), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(mVertexPosition), &mVertexPosition[0]);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(mVertexPosition), sizeof(mVertexNormals), &mVertexNormals[0]);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(mVertexPosition) + sizeof(mVertexNormals), sizeof(mTexCoords), &mTexCoords[0]);

	// Make sure no-one else inadvertently messes around with this mesh data.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	mDataSet = true;
}