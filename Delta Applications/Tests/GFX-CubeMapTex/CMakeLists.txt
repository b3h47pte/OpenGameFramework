set(TEST_SOURCE 
	GFX-CubeMapTex.cpp
)

add_executable(GFX-CubeMapTex ${TEST_SOURCE})

target_link_libraries(GFX-CubeMapTex SDL2)
target_link_libraries(GFX-CubeMapTex SDL2main)
target_link_libraries(GFX-CubeMapTex freeimage)
target_link_libraries(GFX-CubeMapTex ${OpenGL_Library})
target_link_libraries(GFX-CubeMapTex ${GLEW_Library})

target_link_libraries(GFX-CubeMapTex Core)
target_link_libraries(GFX-CubeMapTex Gfx)


