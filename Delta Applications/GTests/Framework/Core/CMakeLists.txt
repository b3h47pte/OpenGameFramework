set(CORE_GTEST_SOURCE 
	"$ENV{GTEST_DIR}/src/gtest_main.cc" message_server_gtest.cpp 
	message_client_gtest.cpp error_catch_gtest.cpp
)

add_executable(CORE-GTest ${CORE_GTEST_SOURCE})
target_link_libraries(CORE-GTest Core)

target_link_libraries(CORE-GTest gtest)
target_link_libraries(CORE-GTest gtest_main)
target_link_libraries(CORE-GTest gmock)
