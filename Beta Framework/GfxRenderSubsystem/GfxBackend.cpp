#include "GfxBackend.h"
#include "MeshRenderable.h"
#include "GfxViewport.h"
#include "GfxCamera.h"
#include "TextureManager.h"
#include "GfxShaderInstance.h"

GfxBackend::GfxBackend(void)
{
}


GfxBackend::~GfxBackend(void)
{
}

/*
 * Tick renders all elements so perform the clear here (glClear) so that we don't wipe elements from a previous viewport.
 */
void GfxBackend::PreTick() {
  OGL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

/*
 * Tick to render all renderables.
 */
void GfxBackend::Tick(float inDeltaTime) {
	Render(inDeltaTime);	
}

/*
 * Render function.
 */ 
void GfxBackend::Render(float inDeltaTime) {
	// Set Viewport Details
	int x;
	int y;
	mActiveViewport->GetViewportPosition(x, y);
  OGL_CALL(glViewport(x, y,
    mActiveViewport->GetViewportWidth(), 
    mActiveViewport->GetViewportHeight()));

	glm::mat4 projectionMat = mActiveViewport->GetCamera()->GetProjectionMatrix();
	glm::mat4 viewMat = mActiveViewport->GetCamera()->GetTransformationMatrix();
	
	SShaderData projData;
	projData.mData = &projectionMat;
	projData.mType = ESDT_MATRIX4x4;
	projData.mUniform = true;

	SShaderData viewData;
	viewData.mData = &viewMat;
	viewData.mType = ESDT_MATRIX4x4;
	viewData.mUniform = true;

	
	// Step through all registered renderables and grab their information to render using the 
  // lights in the scene.
	IRenderable* curRenderPtr = mRenderableList.GetHeadElement();
  ILight* curLightPtr = mLightList.GetHeadElement();
  while (curLightPtr) {
    // Go through each light in the scene and use its shader to render the mesh. 
    // For each renderable instance, set its material data as necessary into shader.
    GfxShaderInstance* lightShader = curLightPtr->GetShader();
    OGL_CALL(glUseProgram(lightShader->GetId()));

    // Set uniform information about the light. 
    
	  while(curRenderPtr) {	
		  // Renderable will take care of setting its data up so its children can render
		  if (curRenderPtr->PrepareToRender()) {
			  // For each Renderable, go through its instances and grab 
			  // their appropriate information so we can draw 
			  // everything with the same material and mesh in one go
			  IRenderableInstance* curInstPtr = curRenderPtr->mInstanceList.GetHeadElement();
			
			  while (curInstPtr) {
				  curInstPtr->PrepareRender();

				  // Set uniforms that ALL shaders must accept. PROJECTION and VIEW matrices.
				  // MODEL matrix will be determined by the mesh/renderable itself. 
				  // TODO: Generalize this based on the actual object...somehow.
				  int projIndx = curInstPtr->GetUniformLocation("projection_matrix");
				  curInstPtr->SetInternalShaderData(projIndx, projData);

				  int viewIndx = curInstPtr->GetUniformLocation("view_matrix");
				  curInstPtr->SetInternalShaderData(viewIndx, viewData);

				  curInstPtr->OnRender();
				  curInstPtr->FinishRender();
				  curInstPtr = curRenderPtr->mInstanceList.GetNextElement(curInstPtr);
			  }

			
			  curRenderPtr->FinishRender();
		  }
		
		  curRenderPtr = mRenderableList.GetNextElement(curRenderPtr);
	  }
	  
    curLightPtr = mLightList.GetNextElement(curLightPtr);
  }
	
}

/*
 * Register Renderable with the backend which will guarantee that an object is only ever registered once and that it will be rendered on screen if necessary.
 */
void GfxBackend::RegisterRenderable(IRenderable* inRenderable) {
	// First make sure the renderable hasn't been registered and then proceed to put the renderable into the right data structure
	if (!inRenderable->mIsRegistered) {
		inRenderable->mIsRegistered = true;
		mRenderableList.AppendElement(inRenderable);
	}
}

void GfxBackend::RegisterLight(ILight* inLight) {
  if (!inLight->GetIsRegistered()) {
    inLight->SetIsRegistered(true);
    inLight->InitializeLight();
    mLightList.AppendElement(inLight);
  }
}

/*
 * Initialize Graphics API (OpenGL, DirectX, whatever).
 * Should only be called ONCE.
 */
bool GfxBackend::InitializeGraphicsAPI(int width, int height) {
	// Initialize some basic GLEW/OpenGL stuff if we can -- otherwise wait for the user to pass in the context and the like
	GLenum err;

	glewExperimental = GL_TRUE;
	err = glewInit();
	if (GLEW_OK != err) {
		return false;
	}
  // NOTE: glewInit(), even with glewExperimental, may leave us with a OpenGL GL_INVALID_ENUM error.
  while ((err = glGetError()) != GL_NO_ERROR);


	mCurrentTextureManager = GetTextureManager();
	if (!mCurrentTextureManager) {
		return false;
	}
  
  OGL_CALL(glEnable(GL_DEPTH_TEST));

  OGL_CALL(glViewport(0, 0, width, height));
  OGL_CALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

	return true;
}
