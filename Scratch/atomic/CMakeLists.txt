####################################################################################################
### (c) Laurentiu Cristofor
### This file is made available under the MIT license.
### Do not use it if you have not received an associated LICENSE file.
####################################################################################################

# Set the project name.
project(atomic)

# Our main target.
add_executable(atomic atomic.cpp)
target_link_libraries(atomic PRIVATE rt)
set_target_properties(atomic PROPERTIES COMPILE_FLAGS "${ATOMIC_COMPILE_FLAGS}")
set_target_properties(atomic PROPERTIES LINK_FLAGS "${ATOMIC_LINK_FLAGS}")
