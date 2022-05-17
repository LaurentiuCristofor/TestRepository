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
set(SCRATCH_COMPILE_FLAGS "-c -Wall -Wextra -ggdb")
set(SCRATCH_LINK_FLAGS "-ggdb -pthread")

# Add individual folders.
add_subdirectory(AccessControl)
add_subdirectory(atomic)
add_subdirectory(flatbuffers)
add_subdirectory(jni)
add_subdirectory(airport)

# Helper function for setting up our tests.
function(set_test target arg result)
  add_test(NAME Test_${target}_${arg} COMMAND ${target} ${arg})
  set_tests_properties(Test_${target}_${arg} PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endfunction(set_test)

# Set tests.
set(TEST_SUCCESS "All tests passed!")

# Common tests.
set_test(TestRetailAssert 0 ${TEST_SUCCESS})
set_test(TestAccessControl 0 ${TEST_SUCCESS})

