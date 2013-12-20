cmake_minimum_required(VERSION 2.6)
project(OGF)

# C++11 is necessary
add_definitions(-std=c++11)
add_definitions(-Wc++11-extensions)
add_definitions(-fms-extensions)

# Include directories that are essential for everybody
include_directories(Extras/)

# SDL
include_directories(Extras/SDL/include)

# FreeImage
include_directories(Extras/FreeImage/Source)

# FMOD
include_directories(Extras/FMOD/api/inc)

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# ALPHA TOOLS CURRENTLY CAN NOT BE BUILT BY NON-WINDOWS PLATFORMS
#add_subdirectory(Alpha\ Tools)

# BETA FRAMEWORK
add_subdirectory(Beta\ Framework)

# DELTA APPLICATIONS
#add_subdirectory(Delta\ Applications)
