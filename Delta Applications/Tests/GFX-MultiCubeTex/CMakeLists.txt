set(TEST_SOURCE 
	GFX-MultiCubeTex.cpp
)

add_executable(GFX-MultiCubeTex ${TEST_SOURCE})

target_link_libraries(GFX-MultiCubeTex SDL2)
target_link_libraries(GFX-MultiCubeTex SDL2main)
target_link_libraries(GFX-MultiCubeTex freeimage)
target_link_libraries(GFX-MultiCubeTex ${OpenGL_Library})
target_link_libraries(GFX-MultiCubeTex ${GLEW_Library})

target_link_libraries(GFX-MultiCubeTex Core)
target_link_libraries(GFX-MultiCubeTex Gfx)


