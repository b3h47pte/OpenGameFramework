set(TEST_SOURCE 
	GFX-MultiColor.cpp
)

add_executable(GFX-MultiColor ${TEST_SOURCE})

target_link_libraries(GFX-MultiColor SDL2)
target_link_libraries(GFX-MultiColor SDL2main)
target_link_libraries(GFX-MultiColor ${OpenGL_Library})
target_link_libraries(GFX-MultiColor ${GLEW_Library})

target_link_libraries(GFX-MultiColor Core)
target_link_libraries(GFX-MultiColor Gfx)


