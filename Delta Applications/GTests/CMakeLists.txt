# Gets rid of warning in gmock-matchers.
add_definitions(-Wno-microsoft)

include_directories(./)
include_directories(${PROJECT_SOURCE_DIR}/Beta\ Framework/Core)
include_directories(${PROJECT_SOURCE_DIR}/Beta\ Framework/GfxRenderSubsytem)

include_directories("$ENV{GTEST_DIR}/include")
link_directories("$ENV{GTEST_DIR}/$ENV{GTEST_LIB}")

include_directories("$ENV{GMOCK_DIR}/include")
link_directories("$ENV{GMOCK_DIR}/$ENV{GMOCK_LIB}")

add_subdirectory(Framework)

