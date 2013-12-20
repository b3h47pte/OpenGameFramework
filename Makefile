# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = "/Applications/CMake 2.8-12.app/Contents/bin/cmake"

# The command to remove a file.
RM = "/Applications/CMake 2.8-12.app/Contents/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = "/Applications/CMake 2.8-12.app/Contents/bin/ccmake"

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/michaelbao/Code/ogf

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/michaelbao/Code/ogf

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	"/Applications/CMake 2.8-12.app/Contents/bin/ccmake" -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	"/Applications/CMake 2.8-12.app/Contents/bin/cmake" -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/michaelbao/Code/ogf/CMakeFiles /Users/michaelbao/Code/ogf/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/michaelbao/Code/ogf/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named Core

# Build rule for target.
Core: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Core
.PHONY : Core

# fast build rule for target.
Core/fast:
	$(MAKE) -f "Beta Framework/Core/CMakeFiles/Core.dir/build.make" "Beta Framework/Core/CMakeFiles/Core.dir/build"
.PHONY : Core/fast

#=============================================================================
# Target rules for targets named Gfx

# Build rule for target.
Gfx: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Gfx
.PHONY : Gfx

# fast build rule for target.
Gfx/fast:
	$(MAKE) -f "Beta Framework/GfxRenderSubsystem/CMakeFiles/Gfx.dir/build.make" "Beta Framework/GfxRenderSubsystem/CMakeFiles/Gfx.dir/build"
.PHONY : Gfx/fast

#=============================================================================
# Target rules for targets named Audio

# Build rule for target.
Audio: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Audio
.PHONY : Audio

# fast build rule for target.
Audio/fast:
	$(MAKE) -f "Beta Framework/AudioSubsystem/CMakeFiles/Audio.dir/build.make" "Beta Framework/AudioSubsystem/CMakeFiles/Audio.dir/build"
.PHONY : Audio/fast

#=============================================================================
# Target rules for targets named Network

# Build rule for target.
Network: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Network
.PHONY : Network

# fast build rule for target.
Network/fast:
	$(MAKE) -f "Beta Framework/NetworkLibrary/CMakeFiles/Network.dir/build.make" "Beta Framework/NetworkLibrary/CMakeFiles/Network.dir/build"
.PHONY : Network/fast

#=============================================================================
# Target rules for targets named CORE-ConfigReadWriteTest

# Build rule for target.
CORE-ConfigReadWriteTest: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 CORE-ConfigReadWriteTest
.PHONY : CORE-ConfigReadWriteTest

# fast build rule for target.
CORE-ConfigReadWriteTest/fast:
	$(MAKE) -f "Delta Applications/Tests/CORE-ConfigReadWriteTest/CMakeFiles/CORE-ConfigReadWriteTest.dir/build.make" "Delta Applications/Tests/CORE-ConfigReadWriteTest/CMakeFiles/CORE-ConfigReadWriteTest.dir/build"
.PHONY : CORE-ConfigReadWriteTest/fast

#=============================================================================
# Target rules for targets named CORE-MessagingTest

# Build rule for target.
CORE-MessagingTest: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 CORE-MessagingTest
.PHONY : CORE-MessagingTest

# fast build rule for target.
CORE-MessagingTest/fast:
	$(MAKE) -f "Delta Applications/Tests/CORE-MessagingTest/CMakeFiles/CORE-MessagingTest.dir/build.make" "Delta Applications/Tests/CORE-MessagingTest/CMakeFiles/CORE-MessagingTest.dir/build"
.PHONY : CORE-MessagingTest/fast

#=============================================================================
# Target rules for targets named GFX-CameraMoveTest

# Build rule for target.
GFX-CameraMoveTest: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 GFX-CameraMoveTest
.PHONY : GFX-CameraMoveTest

# fast build rule for target.
GFX-CameraMoveTest/fast:
	$(MAKE) -f "Delta Applications/Tests/GFX-CameraMoveTest/CMakeFiles/GFX-CameraMoveTest.dir/build.make" "Delta Applications/Tests/GFX-CameraMoveTest/CMakeFiles/GFX-CameraMoveTest.dir/build"
.PHONY : GFX-CameraMoveTest/fast

#=============================================================================
# Target rules for targets named GFX-TextureTest

# Build rule for target.
GFX-TextureTest: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 GFX-TextureTest
.PHONY : GFX-TextureTest

# fast build rule for target.
GFX-TextureTest/fast:
	$(MAKE) -f "Delta Applications/Tests/GFX-TextureTest/CMakeFiles/GFX-TextureTest.dir/build.make" "Delta Applications/Tests/GFX-TextureTest/CMakeFiles/GFX-TextureTest.dir/build"
.PHONY : GFX-TextureTest/fast

#=============================================================================
# Target rules for targets named GfxRenderExample

# Build rule for target.
GfxRenderExample: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 GfxRenderExample
.PHONY : GfxRenderExample

# fast build rule for target.
GfxRenderExample/fast:
	$(MAKE) -f "Delta Applications/Tests/GfxRenderExample/CMakeFiles/GfxRenderExample.dir/build.make" "Delta Applications/Tests/GfxRenderExample/CMakeFiles/GfxRenderExample.dir/build"
.PHONY : GfxRenderExample/fast

#=============================================================================
# Target rules for targets named GfxViewportTest

# Build rule for target.
GfxViewportTest: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 GfxViewportTest
.PHONY : GfxViewportTest

# fast build rule for target.
GfxViewportTest/fast:
	$(MAKE) -f "Delta Applications/Tests/GfxViewportTest/CMakeFiles/GfxViewportTest.dir/build.make" "Delta Applications/Tests/GfxViewportTest/CMakeFiles/GfxViewportTest.dir/build"
.PHONY : GfxViewportTest/fast

#=============================================================================
# Target rules for targets named SDL-InputTest

# Build rule for target.
SDL-InputTest: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 SDL-InputTest
.PHONY : SDL-InputTest

# fast build rule for target.
SDL-InputTest/fast:
	$(MAKE) -f "Delta Applications/Tests/SDL-InputTest/CMakeFiles/SDL-InputTest.dir/build.make" "Delta Applications/Tests/SDL-InputTest/CMakeFiles/SDL-InputTest.dir/build"
.PHONY : SDL-InputTest/fast

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... Core"
	@echo "... Gfx"
	@echo "... Audio"
	@echo "... Network"
	@echo "... CORE-ConfigReadWriteTest"
	@echo "... CORE-MessagingTest"
	@echo "... GFX-CameraMoveTest"
	@echo "... GFX-TextureTest"
	@echo "... GfxRenderExample"
	@echo "... GfxViewportTest"
	@echo "... SDL-InputTest"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

