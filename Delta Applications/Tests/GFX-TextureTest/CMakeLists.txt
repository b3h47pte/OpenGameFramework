set(TEST_SOURCE 
	GFX-TextureTest.cpp stdafx.cpp
)

add_executable(GFX-TextureTest ${TEST_SOURCE})

target_link_libraries(GFX-TextureTest SDL2)
target_link_libraries(GFX-TextureTest SDL2main)
target_link_libraries(GFX-TextureTest freeimage)
target_link_libraries(GFX-TextureTest ${OpenGL_Library})
target_link_libraries(GFX-TextureTest ${GLEW_Library})

target_link_libraries(GFX-TextureTest Core)
target_link_libraries(GFX-TextureTest Gfx)

