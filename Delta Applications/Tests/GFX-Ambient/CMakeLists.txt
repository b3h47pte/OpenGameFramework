set(TEST_SOURCE 
	GFX-Ambient.cpp
)

add_executable(GFX-Ambient ${TEST_SOURCE})

target_link_libraries(GFX-Ambient SDL2)
target_link_libraries(GFX-Ambient SDL2main)
target_link_libraries(GFX-Ambient ${OpenGL_Library})
target_link_libraries(GFX-Ambient ${GLEW_Library})

target_link_libraries(GFX-Ambient Core)
target_link_libraries(GFX-Ambient Gfx)


