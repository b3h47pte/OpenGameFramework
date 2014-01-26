set(TEST_SOURCE 
	GFX-MultiCube.cpp
)

add_executable(GFX-MultiCube ${TEST_SOURCE})

target_link_libraries(GFX-MultiCube SDL2)
target_link_libraries(GFX-MultiCube SDL2main)
target_link_libraries(GFX-MultiCube ${OpenGL_Library})
target_link_libraries(GFX-MultiCube ${GLEW_Library})

target_link_libraries(GFX-MultiCube Core)
target_link_libraries(GFX-MultiCube Gfx)


