####################################################################################################
### (c) Laurentiu Cristofor
### This file is made available under the MIT license.
### Do not use it if you have not received an associated LICENSE file.
####################################################################################################

cmake_minimum_required(VERSION 3.11)

# Set the project name.
project(Experiment)

# Build java code and package it in a jar file. Also generate native headers.
add_jar(Experiment
    Experiment.java
    DataContainer.java
  GENERATE_NATIVE_HEADERS experiment_jni_headers
  DESTINATION ${PROJECT_BINARY_DIR})
get_target_property(EXPERIMENT_JAR Experiment JAR_FILE)

# Configure build of native C++ library.
add_library(native_experiment SHARED Experiment.cpp)
target_include_directories(native_experiment PRIVATE ${PROJECT_BINARY_DIR})
target_include_directories(native_experiment PRIVATE ${JNI_INCLUDE_DIRS})
target_link_libraries(native_experiment PRIVATE experiment_jni_headers)
set_target_properties(native_experiment PROPERTIES COMPILE_FLAGS "${SCRATCH_COMPILE_FLAGS}")
set_target_properties(native_experiment PROPERTIES LINK_FLAGS "${SCRATCH_LINK_FLAGS}")

# Add a test that executes the Java program.
add_test(NAME test_jni_experiment COMMAND ${Java_JAVA_EXECUTABLE} -Djava.library.path=. -cp ${EXPERIMENT_JAR} Experiment)
