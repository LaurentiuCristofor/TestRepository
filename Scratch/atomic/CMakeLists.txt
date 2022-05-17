####################################################################################################
### (c) Laurentiu Cristofor
### This file is made available under the MIT license.
### Do not use it if you have not received an associated LICENSE file.
####################################################################################################

cmake_minimum_required(VERSION 3.10)

enable_testing()

# Set the project name.
project(atomic)

# Specify the C++ standard.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set some global variables.
set(GAIA_COMPILE_FLAGS "-c -Wall -Wextra -ggdb")
set(GAIA_LINK_FLAGS "-ggdb -pthread")

# Our main target.
add_executable(atomic atomic.cpp)
target_link_libraries(atomic PRIVATE rt)
set_target_properties(atomic PROPERTIES COMPILE_FLAGS "${GAIA_COMPILE_FLAGS}")
set_target_properties(atomic PROPERTIES LINK_FLAGS "${GAIA_LINK_FLAGS}")
