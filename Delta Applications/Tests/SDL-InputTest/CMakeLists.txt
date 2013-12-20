set(TEST_SOURCE 
	SDL-InputTest.cpp stdafx.cpp
)

add_executable(SDL-InputTest ${TEST_SOURCE})

target_link_libraries(SDL-InputTest SDL2)
target_link_libraries(SDL-InputTest SDL2main)
target_link_libraries(SDL-InputTest ${OpenGL_Library})
target_link_libraries(SDL-InputTest ${GLEW_Library})

target_link_libraries(SDL-InputTest Core)
target_link_libraries(SDL-InputTest Gfx)


