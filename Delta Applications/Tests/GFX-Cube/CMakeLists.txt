set(TEST_SOURCE 
	GFX-Cube.cpp
)

add_executable(GFX-Cube ${TEST_SOURCE})

target_link_libraries(GFX-Cube SDL2)
target_link_libraries(GFX-Cube SDL2main)
target_link_libraries(GFX-Cube ${OpenGL_Library})
target_link_libraries(GFX-Cube ${GLEW_Library})

target_link_libraries(GFX-Cube Core)
target_link_libraries(GFX-Cube Gfx)


