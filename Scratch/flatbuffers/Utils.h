////////////////////////////////////////////////////////////////////////////////////////////////////
/// (c) Laurentiu Cristofor
/// This file is made available under the MIT license.
/// Do not use it if you have not received an associated LICENSE file.
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

// Load data from a file. Caller is responsible for deallocating the buffer memory.
void LoadFileData(const char* filename, char*& data, int& length);
