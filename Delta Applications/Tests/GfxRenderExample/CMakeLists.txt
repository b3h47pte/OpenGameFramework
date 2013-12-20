set(TEST_SOURCE 
	GfxRenderExample.cpp stdafx.cpp
)

add_executable(GfxRenderExample ${TEST_SOURCE})

target_link_libraries(GfxRenderExample SDL2)
target_link_libraries(GfxRenderExample SDL2main)
target_link_libraries(GfxRenderExample ${OpenGL_Library})
target_link_libraries(GfxRenderExample ${GLEW_Library})

target_link_libraries(GfxRenderExample Core)
target_link_libraries(GfxRenderExample Gfx)


