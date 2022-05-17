////////////////////////////////////////////////////////////////////////////////////////////////////
/// (c) Laurentiu Cristofor
/// This file is made available under the MIT license.
/// Do not use it if you have not received an associated LICENSE file.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "HelloWorld.h"

#include <iostream>

JNIEXPORT void JNICALL Java_HelloWorld_helloWorld(JNIEnv*, jobject)
{
    std::cout << "Hello from deep inside C++ !!!" << std::endl;
}
