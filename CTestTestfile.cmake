# CMake generated Testfile for 
# Source directory: /Users/michaelbao/Code/ogf
# Build directory: /Users/michaelbao/Code/ogf
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
ADD_TEST(CoreGTest "Delta Applications/GTests/Framework/Core/CORE-GTest")
SUBDIRS(Beta Framework)
SUBDIRS(Delta Applications)
