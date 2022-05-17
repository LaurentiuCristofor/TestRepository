////////////////////////////////////////////////////////////////////////////////////////////////////
/// (c) Laurentiu Cristofor
/// This file is made available under the MIT license.
/// Do not use it if you have not received an associated LICENSE file.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "Constants.hpp"
#include "RetailAssert.hpp"

using namespace std;
using namespace LaurentiuCristofor;

void TestRetailAssert();

int main()
{
    TestRetailAssert();

    cout << endl << AllTestsPassed << endl;
}

void TestRetailAssert()
{
    cout << endl << DebugOutputSeparatorLineStart << endl;
    cout << "*** RetailAssert tests started ***" << endl;
    cout << DebugOutputSeparatorLineEnd << endl;

    try
    {
        RetailAssert(true, "Unexpected triggering of retail assert!");
    }
    catch(const std::exception& e)
    {
        cout << "ERROR: An unexpected exception was thrown!" << endl;
        cerr << "ERROR: Exception message: " << e.what() << '\n';
    }

    cout << "PASSED: No exception was thrown by RetailAssert on a true condition!" << endl;

    try
    {
        RetailAssert(false, "Expected triggering of retail assert.");
    }
    catch(const std::exception& e)
    {
        cout << "PASSED: An exception was thrown by RetailAssert on a false condition, as expected." << endl;
        cerr << "PASSED: Exception message: " << e.what() << '\n';
    }

    cout << endl << DebugOutputSeparatorLineStart << endl;
    cout << "*** RetailAssert tests ended ***" << endl;
    cout << DebugOutputSeparatorLineEnd << endl;
}
