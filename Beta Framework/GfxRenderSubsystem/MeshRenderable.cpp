#include "MeshRenderable.h"
#include "MeshRenderableInstance.h"
#include "GfxSubsystem.h"
#include "GfxBackend.h"

MeshRenderable::MeshRenderable(void) {
}


MeshRenderable::~MeshRenderable(void) {
  OGL_CALL(glDeleteBuffers(1, &mVBO));
  OGL_CALL(glDeleteVertexArrays(1, &mVAO));
  OGL_CALL(glDeleteBuffers(1, &mEBO));
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
  OGL_CALL(glBindVertexArray(mVAO));
  OGL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO));
  return true;
}

/*
 * Finish Rendering by unbinding buffers so that these buffers aren't mistakenly read from/modified.
 */
bool MeshRenderable::FinishRender() {
  OGL_CALL(glBindVertexArray(0));
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
 * FinalizeData will take the vertex/shader/material data that was input 
 * and then create the necessary OpenGL buffers and shaders and retain the
 * information necessary for this renerable to reload the state later for rendering.  * Also handled registering the mesh with the graphics subsystem.
 */
void MeshRenderable::FinalizeData() {
  
  // Create the VAO to hold the mesh's data (color, position, etc.)
  OGL_CALL(glGenVertexArrays(1, &mVAO));
  OGL_CALL(glBindVertexArray(mVAO));

  // Create Element Array Buffer (EBO) to hold the indicies of vertices
  OGL_CALL(glGenBuffers(1, &mEBO));
  OGL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO));
  OGL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)* mTriangleIndices.size(), &mTriangleIndices[0], GL_STATIC_DRAW));

  // Setup VBO
  OGL_CALL(glGenBuffers(1, &mVBO));
  OGL_CALL(glBindBuffer(GL_ARRAY_BUFFER, mVBO));
  OGL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * mVertexPosition.size() + sizeof(glm::vec4) * mVertexNormals.size()
    + sizeof(glm::vec2) * mTexCoords.size()
    + GetSizeOfExternalVertexAttr(), NULL, GL_STATIC_DRAW));

  // Vertex Position
  OGL_CALL(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec4) * mVertexPosition.size(), &mVertexPosition[0]));

  // Vertex Normals
  OGL_CALL(glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * mVertexPosition.size(), sizeof(glm::vec4) * mVertexNormals.size(), &mVertexNormals[0]));

  // Vertex Tex Coord
  OGL_CALL(glBufferSubData(GL_ARRAY_BUFFER,
    sizeof(glm::vec4) * mVertexPosition.size() + 
      sizeof(glm::vec4) * mVertexNormals.size(), 
    sizeof(glm::vec2) * mTexCoords.size(), &mTexCoords[0]));
  
  OGL_CALL(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0));
  OGL_CALL(glEnableVertexAttribArray(0));

  OGL_CALL(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0,
    (void*) (sizeof(glm::vec4) * mVertexPosition.size())));
  OGL_CALL(glEnableVertexAttribArray(1));

  OGL_CALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0,
    (void*) (sizeof(glm::vec4) * mVertexPosition.size() + 
    sizeof(glm::vec4) * mVertexNormals.size())));
  OGL_CALL(glEnableVertexAttribArray(2));

  // Load in and Enable External Per-Vertex Attributes.
  LoadExternalPerVertexAttr(3,
    sizeof(glm::vec4) * mVertexPosition.size() + 
    sizeof(glm::vec4) * mVertexNormals.size() + 
    sizeof(glm::vec2) * mTexCoords.size());

  mDataSet = true;
  // Register Ourselves
  GetGfxSubsystem(NULL)->RegisterRenderable(this);
  OnRegistration();

  // Make sure no-one else inadvertently messes around with this mesh data.
  OGL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
  OGL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
  OGL_CALL(glBindVertexArray(0));
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
 * Support Externally Declared Per-Vertex Attributes.
 */
size_t MeshRenderable::GetSizeOfExternalVertexAttr() const {
  size_t size = 0;
  size_t mul;
  for (auto pvd : mExternalPerVertexAttr) {
    switch (pvd.componentCount) {
    case 1:
      mul = sizeof(float);
      break;
    case 2:
      mul = sizeof(glm::vec2);
      break;
    case 3:
      mul = sizeof(glm::vec3);
      break;
    case 4:
      mul = sizeof(glm::vec4);
      break;
    default:
      mul = 0;
      break;
    }
    size += mul * pvd.data.size();
  }
  return size;
}

void MeshRenderable::LoadExternalPerVertexAttr(int startIdx, size_t startSize) {
  size_t mul;
  for (auto pvd : mExternalPerVertexAttr) {
    switch (pvd.componentCount) {
    case 1:
      mul = sizeof(float);
      break;
    case 2:
      mul = sizeof(glm::vec2);
      break;
    case 3:
      mul = sizeof(glm::vec3);
      break;
    case 4:
      mul = sizeof(glm::vec4);
      break;
    default:
      mul = 0;
      break;
    }

    if (mul == 0)
      continue;

    OGL_CALL(glBufferSubData(GL_ARRAY_BUFFER, startSize,
      mul * pvd.data.size(), &pvd.data[0]));

    OGL_CALL(glVertexAttribPointer(startIdx, pvd.componentCount, GL_FLOAT, GL_FALSE, 0,
      (void*)startSize));
    OGL_CALL(glEnableVertexAttribArray(startIdx));

    startSize += mul * pvd.data.size();
  }
}
