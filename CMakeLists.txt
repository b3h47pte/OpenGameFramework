cmake_minimum_required(VERSION 2.6)
project(OGF)
include(CTest)

# C++11 is necessary
add_definitions(-std=c++11)
add_definitions(-Wc++11-extensions)
add_definitions(-fms-extensions)

# Other necssary C++ items
add_definitions(-Wall)
add_definitions(-g)

# Include directories that are essential for everybody
include_directories(Extras/)

# Force /usr/include to be included on Mac platforms (it doesn't get included 
# when doing include_directories for GLEW later.
if (APPLE)
	add_definitions(-I/usr/include)
endif(APPLE)

# SDL
include_directories(Extras/SDL/include)
link_directories(${PROJECT_SOURCE_DIR}/Extras/SDL/build)
link_directories(${PROJECT_SOURCE_DIR}/Extras/SDL/build/.libs)


# FreeImage
include_directories(Extras/FreeImage/Source)
IF (APPLE)
	link_directories(${PROJECT_SOURCE_DIR}/Extras/FreeImage/Dist)
ENDIF (APPLE)

# FMOD
include_directories(Extras/FMOD/api/inc)

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
find_library(OpenGL_Library OpenGL)

# GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})
find_library(GLEW_Library GLEW)

# ALPHA TOOLS CURRENTLY CAN NOT BE BUILT BY NON-WINDOWS PLATFORMS
#add_subdirectory(Alpha\ Tools)

# BETA FRAMEWORK
add_subdirectory(Beta\ Framework)

# DELTA APPLICATIONS
add_subdirectory(Delta\ Applications)

set(GTEST_SUBDIR 
	Delta\ Applications/GTests/
)

add_test(CoreGTestMessageServer ${GTEST_SUBDIR}/Framework/Core/CORE-GTest-MessageServer)
add_test(CoreGTestMessageClient ${GTEST_SUBDIR}/Framework/Core/CORE-GTest-MessageClient)
add_test(CoreGTestErrorCatch ${GTEST_SUBDIR}/Framework/Core/CORE-GTest-ErrorCatch)
add_test(CoreGTestIntrList ${GTEST_SUBDIR}/Framework/Core/CORE-GTest-IntrusiveLink)
add_test(CoreGTestWfile ${GTEST_SUBDIR}/Framework/Core/CORE-GTest-Wfile)
add_test(CoreGTestConfigFile ${GTEST_SUBDIR}/Framework/Core/CORE-GTest-ConfigFile)
add_test(CoreGTestWorldObject ${GTEST_SUBDIR}/Framework/Core/CORE-GTest-WorldObject)

