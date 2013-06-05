#include "GfxBackend.h"
#include "MeshRenderable.h"
#include "GfxViewport.h"
#include "GfxCamera.h"

GfxBackend::GfxBackend(void)
{
}


GfxBackend::~GfxBackend(void)
{
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
	glViewport(x, y, mActiveViewport->GetViewportWidth(), mActiveViewport->GetViewportHeight());

	glm::mat4 camPerspective = glm::perspective(mActiveViewport->GetCamera()->GetFOV(), 
		mActiveViewport->GetCamera()->GetAspectRatio(), mActiveViewport->GetCamera()->GetZNear(),
		mActiveViewport->GetCamera()->GetZFar());
	
	SShaderData projData;
	projData.mData = &camPerspective;
	projData.mType = ESDT_MATRIX4x4;
	projData.mUniform = true;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Step through all registered renderables anx	d grab their information to render
	IRenderable* curRenderPtr = mRenderableList.GetHeadElement();
	while(curRenderPtr) {
		
		// Renderable will take care of setting its data up so its children can render
		if (curRenderPtr->PrepareToRender()) {

			// For each Renderable, go through its instances and grab their appropriate information so we can draw 
			// everything with the same material and mesh in one go
			IRenderableInstance* curInstPtr = curRenderPtr->mInstanceList.GetHeadElement();
			
			

			while (curInstPtr) {
				GLuint shaderProg = curInstPtr->GetShaderProgram();

				curInstPtr->PrepareRender();
				// Set uniforms that ALL shaders must accept.

				int projIndx = curInstPtr->GetUniformLocation("projection_matrix");
				curInstPtr->SetInternalShaderData(projIndx, &projData);

				curInstPtr->OnRender();
				curInstPtr->FinishRender();
				curInstPtr = curRenderPtr->mInstanceList.GetNextElement(curInstPtr);
			}

			
			curRenderPtr->FinishRender();
		}
		
		curRenderPtr = mRenderableList.GetNextElement(curRenderPtr);
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

/*
 * Initialize Graphics API (OpenGL, DirectX, whatever).
 * Should only be called ONCE.
 */
bool GfxBackend::InitializeGraphicsAPI(int width, int height) {
	// Initialize some basic GLEW/OpenGL stuff if we can -- otherwise wait for the user to pass in the context and the like
	GLenum err;
	err = glewInit();
	if (GLEW_OK != err) {
		return false;
	}

	glViewport(0, 0, width, height);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	return true;
}