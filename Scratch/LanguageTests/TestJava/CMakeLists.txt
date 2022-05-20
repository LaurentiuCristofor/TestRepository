####################################################################################################
### (c) Laurentiu Cristofor
### This file is made available under the MIT license.
### Do not use it if you have not received an associated LICENSE file.
####################################################################################################

include(UseJava)

find_package(Java)

# Java AirportDataProcessor project.
if (JAVA_FOUND)
  add_jar(TestJava
    SOURCES
      TestJava.java)
  get_target_property(TEST_JAVA_JAR TestJava JAR_FILE)

  add_custom_target(
    test_java
    ${Java_JAVA_EXECUTABLE} -cp ${TEST_JAVA_JAR} TestJava)
endif()
