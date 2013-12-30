# CMake generated Testfile for 
# Source directory: /Users/michaelbao/Code/ogf
# Build directory: /Users/michaelbao/Code/ogf
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
ADD_TEST(CoreGTestMessageServer "Delta Applications/GTests/Framework/Core/CORE-GTest-MessageServer")
ADD_TEST(CoreGTestMessageClient "Delta Applications/GTests/Framework/Core/CORE-GTest-MessageClient")
ADD_TEST(CoreGTestErrorCatch "Delta Applications/GTests/Framework/Core/CORE-GTest-ErrorCatch")
ADD_TEST(CoreGTestIntrList "Delta Applications/GTests/Framework/Core/CORE-GTest-IntrusiveLink")
ADD_TEST(CoreGTestWfile "Delta Applications/GTests/Framework/Core/CORE-GTest-Wfile")
ADD_TEST(CoreGTestConfigFile "Delta Applications/GTests/Framework/Core/CORE-GTest-ConfigFile")
ADD_TEST(CoreGTestWorldObject "Delta Applications/GTests/Framework/Core/CORE-GTest-WorldObject")
SUBDIRS(Beta Framework)
SUBDIRS(Delta Applications)
