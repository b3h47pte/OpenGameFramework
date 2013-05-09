#include "MeshRenderable.h"
#include "MeshRenderableInstance.h"
#include "GfxSubsystem.h"

MeshRenderable::MeshRenderable(void) {
}


MeshRenderable::~MeshRenderable(void) {
	glDeleteBuffers(1, &mVBO);
	glDeleteVertexArrays(1, &mVAO);
	glDeleteBuffers(1, &mEBO);
	glDeleteProgram(mShaderProgramID);
}

/*
 * Prepare to Render. -- Calls FinalizeData if the user forgets to do this beforehand.
 * 1) Bind Buffers.
 * 2) Prepare shaders.
 */
bool MeshRenderable::PrepareToRender() {
	if (mDataError)
		return false;

	if (!mDataSet) {
		FinalizeData();
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBindVertexArray(mVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glUseProgram(mShaderProgramID);
	return true;
}

/*
 * Finish Rendering by unbinding buffers so that these buffers aren't mistakenly read from/modified.
 */
bool MeshRenderable::FinishRender() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(0);
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
 * for this renerable to reload the state later for rendering. Also handled registering the mesh with the graphics subsystem.
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

	// Load Shader Data 
	// TODO: Load shader program from binary using the shader program name
	int vertID = GfxShaders::GetShaderID(GL_VERTEX_SHADER, mVertexShaderFile);
	if (vertID == -1) {
		if (!GfxShaders::LoadShader(GL_VERTEX_SHADER, mVertexShaderFile, mVertexShaderFile)) {	
			mDataError = true;
			return;
		}
		vertID = GfxShaders::GetShaderID(GL_VERTEX_SHADER, mVertexShaderFile);
	}

	int fragID = GfxShaders::GetShaderID(GL_FRAGMENT_SHADER, mFragShaderFile);
	if (fragID == -1) {
		if (!GfxShaders::LoadShader(GL_FRAGMENT_SHADER, mFragShaderFile, mFragShaderFile)) {
			mDataError = true;
			return;
		}
		fragID = GfxShaders::GetShaderID(GL_FRAGMENT_SHADER, mFragShaderFile);
	}

	// Create Shader Program
	mShaderProgramID = glCreateProgram();
	glAttachShader(mShaderProgramID, vertID);
	glAttachShader(mShaderProgramID, fragID);
	glLinkProgram(mShaderProgramID);

	mDataSet = true;
	// Regeister Ourselves
	GetGfxSubsystem()->RegisterRenderable(this);
	OnRegistration();
}

/*
 * Add vertex.
 */
void MeshRenderable::AddVertex(float p[4], float n[4], float t[2]) {
	mVertexPosition.push_back(glm::vec4(p[0], p[1], p[2], p[3]));
	mVertexNormals.push_back(glm::vec4(n[0], n[1], n[2], n[3]));
	mTexCoords.push_back(glm::vec2(t[0], t[1]));
}

/*
 * Set Shader Program. Not yet implemented. TODO.
 */
void MeshRenderable::SetShaderProgram(const std::string&)  {
	assert(1== 0);
}
/*
 * Set Vertex/Frag Shaders. 
 */
void MeshRenderable::SetVertexShader(const std::string& in) {
	mVertexShaderFile = in;
}

void MeshRenderable::SetFragShader(const std::string& in) {
	mFragShaderFile = in;
}
