set(GTEST_SOURCE 
	"$ENV{GTEST_DIR}/src/gtest_main.cc"
)

add_executable(CORE-GTest-MessageServer ${GTEST_SOURCE} message_server_gtest.cpp )
target_link_libraries(CORE-GTest-MessageServer Core)
target_link_libraries(CORE-GTest-MessageServer gtest)
target_link_libraries(CORE-GTest-MessageServer gtest_main)
target_link_libraries(CORE-GTest-MessageServer gmock)

add_executable(CORE-GTest-MessageClient ${GTEST_SOURCE} message_client_gtest.cpp )
target_link_libraries(CORE-GTest-MessageClient Core)
target_link_libraries(CORE-GTest-MessageClient gtest)
target_link_libraries(CORE-GTest-MessageClient gtest_main)
target_link_libraries(CORE-GTest-MessageClient gmock)

add_executable(CORE-GTest-ErrorCatch ${GTEST_SOURCE} error_catch_gtest.cpp )
target_link_libraries(CORE-GTest-ErrorCatch Core)
target_link_libraries(CORE-GTest-ErrorCatch gtest)
target_link_libraries(CORE-GTest-ErrorCatch gtest_main)
target_link_libraries(CORE-GTest-ErrorCatch gmock)
