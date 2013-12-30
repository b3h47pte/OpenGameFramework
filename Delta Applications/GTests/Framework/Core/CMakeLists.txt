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

add_executable(CORE-GTest-IntrusiveLink ${GTEST_SOURCE} intrusive_link_gtest.cpp )
target_link_libraries(CORE-GTest-IntrusiveLink Core)
target_link_libraries(CORE-GTest-IntrusiveLink gtest)
target_link_libraries(CORE-GTest-IntrusiveLink gtest_main)
target_link_libraries(CORE-GTest-IntrusiveLink gmock)

add_executable(CORE-GTest-Wfile ${GTEST_SOURCE} wfile_gtest.cpp )
target_link_libraries(CORE-GTest-Wfile Core)
target_link_libraries(CORE-GTest-Wfile gtest)
target_link_libraries(CORE-GTest-Wfile gtest_main)
target_link_libraries(CORE-GTest-Wfile gmock)

add_executable(CORE-GTest-ConfigFile ${GTEST_SOURCE} config_file_gtest.cpp )
target_link_libraries(CORE-GTest-ConfigFile Core)
target_link_libraries(CORE-GTest-ConfigFile gtest)
target_link_libraries(CORE-GTest-ConfigFile gtest_main)
target_link_libraries(CORE-GTest-ConfigFile gmock)

add_executable(CORE-GTest-WorldObject ${GTEST_SOURCE} world_object_gtest.cpp )
target_link_libraries(CORE-GTest-WorldObject Core)
target_link_libraries(CORE-GTest-WorldObject gtest)
target_link_libraries(CORE-GTest-WorldObject gtest_main)
target_link_libraries(CORE-GTest-WorldObject gmock)


