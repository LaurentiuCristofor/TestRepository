////////////////////////////////////////////////////////////////////////////////////////////////////
/// (c) Laurentiu Cristofor
/// This file is made available under the MIT license.
/// Do not use it if you have not received an associated LICENSE file.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Utils.h"

#include <fstream>

using namespace std;

void LoadFileData(const char* filename, char*& data, int& length)
{
    ifstream infile;
    infile.open(filename, ios::binary | ios::in);
    infile.seekg(0, ios::end);
    length = infile.tellg();

    infile.seekg(0, ios::beg);
    data = new char[length];
    infile.read(data, length);
    infile.close();
}
