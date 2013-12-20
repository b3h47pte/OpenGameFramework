set(TEST_SOURCE
	CORE-MessagingTest.cpp stdafx.cpp
)

add_executable(CORE-MessagingTest ${TEST_SOURCE})

target_link_libraries(CORE-MessagingTest Core)
