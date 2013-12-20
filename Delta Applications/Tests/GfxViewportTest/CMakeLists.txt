set(TEST_SOURCE 
	GfxViewportTest.cpp stdafx.cpp
)

add_executable(GfxViewportTest ${TEST_SOURCE})

target_link_libraries(GfxViewportTest SDL2)
target_link_libraries(GfxViewportTest SDL2main)
target_link_libraries(GfxViewportTest ${OpenGL_Library})
target_link_libraries(GfxViewportTest ${GLEW_Library})

target_link_libraries(GfxViewportTest Core)
target_link_libraries(GfxViewportTest Gfx)


