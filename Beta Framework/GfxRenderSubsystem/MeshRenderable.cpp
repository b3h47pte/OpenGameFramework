#include "MeshRenderable.h"
#include "MeshRenderableInstance.h"
#include "GfxSubsystem.h"
#include "GfxBackend.h"

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
	glBindVertexArray(mVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glUseProgram(mShaderProgramID);
	
		
	// TEMPORARY
	glm::mat4 projection_matrix = glm::frustum(-1.f, 1.f, -0.75f, 0.75f, 1.f, 500.f);
	glUniformMatrix4fv(mProjectionMatrix, 1, GL_FALSE, glm::value_ptr(projection_matrix));

	return true;
}

/*
 * Finish Rendering by unbinding buffers so that these buffers aren't mistakenly read from/modified.
 */
bool MeshRenderable::FinishRender() {
	glUseProgram(0);
	glBindVertexArray(0);
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
	// Create the VAO to hold the mesh's data (color, position, etc.)
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	// Create Element Array Buffer (EBO) to hold the indicies of vertices
	glGenBuffers(1, &mEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * mTriangleIndices.size(), &mTriangleIndices[0], GL_STATIC_DRAW);

	// Setup VBO
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * mVertexPosition.size() + sizeof(glm::vec4) * mVertexNormals.size() 
		+ sizeof(glm::vec2) * mTexCoords.size(), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec4) * mVertexPosition.size(), &mVertexPosition[0]);

	glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * mVertexPosition.size(), sizeof(glm::vec4) * mVertexNormals.size(), &mVertexNormals[0]);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * mVertexPosition.size() + sizeof(glm::vec4) * mVertexNormals.size(), 
		sizeof(glm::vec2) * mTexCoords.size(), &mTexCoords[0]);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0,  (void*)0);

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

	// Get locations of the matrices
	mProjectionMatrix = glGetUniformLocation(mShaderProgramID, "projection_matrix");
		
	// Make sure no-one else inadvertently messes around with this mesh data.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
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
