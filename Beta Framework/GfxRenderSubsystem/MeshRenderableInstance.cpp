#include "MeshRenderable.h"
#include "MeshRenderableInstance.h"
#include "GfxBackend.h"

MeshRenderableInstance::MeshRenderableInstance(IRenderable* inRen, WorldObject* inObj): IRenderableInstance(inRen, inObj)
{
}


MeshRenderableInstance::~MeshRenderableInstance(void)
{
}

/* 
 * Render Function.
 * Steps:
 *  1) Retrive appropriate transformation data.
 *  2) Set shader data as necessary.
 *  2) Call the OpenGL draw calls necesssary.
 */
void MeshRenderableInstance::OnRender() { 
  IRenderableInstance::OnRender();

  // We need to draw the vertices.
  const MeshRenderable* mesh = 
    dynamic_cast<const MeshRenderable*>(GetParentRenderable());

  glDrawElements(GL_TRIANGLES, mesh->GetVertexCount(), GL_UNSIGNED_INT, (void*)0);
}
