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
	return true;
}

/*
 * Finish Rendering by unbinding buffers so that these buffers aren't mistakenly read from/modified.
 */
bool MeshRenderable::FinishRender() {
	glBindVertexArray(0);
	return true;
}

/*
 * Create a Mesh Renderable Instance for use.
 */
IRenderableInstance* MeshRenderable::CreateRenderableInstance(WorldObject* parObj) {
	IRenderableInstance* newInst = new MeshRenderableInstance(this, parObj);
	
	// Create new shader program
	GLuint newProg = glCreateProgram();
	glAttachShader(newProg, mVertexShaderId);
	glAttachShader(newProg, mFragShaderId);
	glLinkProgram(newProg);
	glDetachShader(newProg, mVertexShaderId);
	glDetachShader(newProg, mFragShaderId);
	newInst->SetShaderProgram(newProg);
	if (glIsProgram(newProg) == GL_FALSE) std::cout << "no longer a program?" <<std::endl;
	
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

	// Vertex Position
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec4) * mVertexPosition.size(), &mVertexPosition[0]);

	// Vertex Normals
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * mVertexPosition.size(), sizeof(glm::vec4) * mVertexNormals.size(), &mVertexNormals[0]);

	// Vertex Tex Coord
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * mVertexPosition.size() + sizeof(glm::vec4) * mVertexNormals.size(), 
		sizeof(glm::vec2) * mTexCoords.size(), &mTexCoords[0]);
	
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0,  (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*) (sizeof(glm::vec4) * mVertexPosition.size()));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*) (sizeof(glm::vec4) * mVertexPosition.size() + sizeof(glm::vec4) * mVertexNormals.size()));
	glEnableVertexAttribArray(2);

	// Load Shader Data 
	// TODO: Load shader program from binary using the shader program name
	mVertexShaderId = GfxShaders::GetShaderID(GL_VERTEX_SHADER, mVertexShaderFile);
	if (mVertexShaderId == -1) {
		if (!GfxShaders::LoadShader(GL_VERTEX_SHADER, mVertexShaderFile, mVertexShaderFile)) {	
			mDataError = true;
			return;
		}
		mVertexShaderId = GfxShaders::GetShaderID(GL_VERTEX_SHADER, mVertexShaderFile);
	}

	mFragShaderId = GfxShaders::GetShaderID(GL_FRAGMENT_SHADER, mFragShaderFile);
	if (mFragShaderId == -1) {
		if (!GfxShaders::LoadShader(GL_FRAGMENT_SHADER, mFragShaderFile, mFragShaderFile)) {
			mDataError = true;
			return;
		}
		mFragShaderId = GfxShaders::GetShaderID(GL_FRAGMENT_SHADER, mFragShaderFile);
	}

	mDataSet = true;
	// Regeister Ourselves
	GetGfxSubsystem(NULL)->RegisterRenderable(this);
	OnRegistration();

	// Make sure no-one else inadvertently messes around with this mesh data.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

/*
 * Add vertex.
 */
void MeshRenderable::AddVertex(float p[4], float n[4], float t[2]) {
	AddVertexPosition(p);
	AddVertexNormal(n);
	AddVertexTex(t);
}

void MeshRenderable::AddVertexPosition(float p[4]) {
	mVertexPosition.push_back(glm::vec4(p[0], p[1], p[2], p[3]));
}

void MeshRenderable::AddVertexNormal(float n[4]) {
	mVertexNormals.push_back(glm::vec4(n[0], n[1], n[2], n[3]));
}

void MeshRenderable::AddVertexTex(float t[2]) {
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
