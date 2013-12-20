set(TEST_SOURCE 
	stdafx.cpp CORE-ConfigReadWriteTest.cpp
)

add_executable(CORE-ConfigReadWriteTest ${TEST_SOURCE})

target_link_libraries(CORE-ConfigReadWriteTest Core)
