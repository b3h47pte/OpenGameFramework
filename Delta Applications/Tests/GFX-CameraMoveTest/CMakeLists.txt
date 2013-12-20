set(TEST_SOURCE 
	GFX-CameraMoveTest.cpp stdafx.cpp
)

add_executable(GFX-CameraMoveTest ${TEST_SOURCE})

target_link_libraries(GFX-CameraMoveTest SDL2)
target_link_libraries(GFX-CameraMoveTest SDL2main)
target_link_libraries(GFX-CameraMoveTest ${OpenGL_Library})
target_link_libraries(GFX-CameraMoveTest ${GLEW_Library})

target_link_libraries(GFX-CameraMoveTest Core)
target_link_libraries(GFX-CameraMoveTest Gfx)


