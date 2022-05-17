####################################################################################################
### (c) Laurentiu Cristofor
### This file is made available under the MIT license.
### Do not use it if you have not received an associated LICENSE file.
####################################################################################################

cmake_minimum_required(VERSION 3.11)

enable_testing()

# Set the project name.
project(Scratch)

# Specify the C++ standard.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set some global variables.
set(GAIA_COMPILE_FLAGS "-c -Wall -Wextra -ggdb")
set(GAIA_LINK_FLAGS "-ggdb -pthread")

# Add individual folders.
add_subdirectory(flatbuffers)
add_subdirectory(jni)
add_subdirectory(airport)
