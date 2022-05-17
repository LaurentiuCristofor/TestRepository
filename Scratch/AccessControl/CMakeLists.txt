####################################################################################################
### (c) Laurentiu Cristofor
### This file is made available under the MIT license.
### Do not use it if you have not received an associated LICENSE file.
####################################################################################################

cmake_minimum_required(VERSION 3.10)

# Set the project name.
project(AccessControl)

# Our main target.
add_library(AccessControl SHARED AccessControl.cpp)
target_include_directories(AccessControl PUBLIC ${PROJECT_SOURCE_DIR})
set_target_properties(AccessControl PROPERTIES COMPILE_FLAGS "${SCRATCH_COMPILE_FLAGS}")

# Our unit tests.
add_executable(TestRetailAssert TestRetailAssert.cpp)
add_executable(TestAccessControl TestAccessControl.cpp)

target_include_directories(TestRetailAssert PRIVATE ${PROJECT_SOURCE_DIR})
target_include_directories(TestAccessControl PRIVATE ${PROJECT_SOURCE_DIR})

target_link_libraries(TestAccessControl PRIVATE AccessControl)
