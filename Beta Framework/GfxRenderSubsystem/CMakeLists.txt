include_directories(../Core)

set(GFX_ALL_SOURCES
	GfxBackend.cpp GfxCamera.cpp GfxShaders.cpp GfxSubsystem.cpp GfxUtility.cpp
	GfxViewport.cpp GfxWindow.cpp IRenderable.cpp IRenderableInstance.cpp
	ITexture.cpp MeshRenderable.cpp MeshRenderableInstance.cpp SDLWindow.cpp
	SDLWindowKeyboard.cpp TextureManager.cpp
)
add_library(Gfx ${GFX_ALL_SOURCES})
