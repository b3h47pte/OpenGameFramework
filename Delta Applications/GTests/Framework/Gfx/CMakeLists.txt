set(GFX_GTEST_SOURCE 
	"$ENV{GTEST_DIR}/src/gtest_main.cc"
)

add_executable(GFX-GTest ${GFX_GTEST_SOURCE})

target_link_libraries(GFX-GTest SDL2)
target_link_libraries(GFX-GTest SDL2main)
target_link_libraries(GFX-GTest ${OpenGL_Library})
target_link_libraries(GFX-GTest ${GLEW_Library})

target_link_libraries(GFX-GTest Core)
target_link_libraries(GFX-GTest Gfx)
target_link_libraries(GFX-GTest gtest)
target_link_libraries(GFX-GTest gtest_main)
