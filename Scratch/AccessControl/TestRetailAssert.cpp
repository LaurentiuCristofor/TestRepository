////////////////////////////////////////////////////////////////////////////////////////////////////
/// (c) Laurentiu Cristofor
/// This file is made available under the MIT license.
/// Do not use it if you have not received an associated LICENSE file.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "Constants.hpp"
#include "Assert.hpp"

using namespace std;
using namespace LaurentiuCristofor;

void TestAssert();

int main()
{
    TestAssert();

    cout << endl << AllTestsPassed << endl;
}

void TestAssert()
{
    cout << endl << DebugOutputSeparatorLineStart << endl;
    cout << "*** ASSERT tests started ***" << endl;
    cout << DebugOutputSeparatorLineEnd << endl;

    ASSERT(true, "Unexpected triggering of retail assert!");

    cout << "PASSED: No exception was thrown by ASSERT on a true condition!" << endl;

    try
    {
        ASSERT(false, "Expected triggering of retail assert.");
        cout << "FAILED: An exception was not thrown by ASSERT on a false condition, as expected." << endl;
        exit(1);
    }
    catch(const std::exception& e)
    {
        cout << "PASSED: An exception was thrown by ASSERT on a false condition, as expected." << endl;
        cerr << "PASSED: Exception message: " << e.what() << '\n';
    }

    cout << endl << DebugOutputSeparatorLineStart << endl;
    cout << "*** ASSERT tests ended ***" << endl;
    cout << DebugOutputSeparatorLineEnd << endl;
}
