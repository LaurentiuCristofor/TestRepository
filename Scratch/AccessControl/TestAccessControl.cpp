////////////////////////////////////////////////////////////////////////////////////////////////////
/// (c) Laurentiu Cristofor
/// This file is made available under the MIT license.
/// Do not use it if you have not received an associated LICENSE file.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "Constants.hpp"
#include "RetailAssert.hpp"
#include "AccessControl.hpp"

using namespace std;
using namespace LaurentiuCristofor;

void TestAccessControl();

int main()
{
    TestAccessControl();

    cout << endl << AllTestsPassed << endl;
}

void TestAccessControl()
{
    cout << endl << DebugOutputSeparatorLineStart << endl;
    cout << ">>> EAccessControl tests started <<<" << endl;
    cout << DebugOutputSeparatorLineEnd << endl;

    cout << "sizeof(AccessControl) = " << sizeof(AccessControl) << endl;

    AccessControl accessControl;
    AccessControl secondAccessControl;
    EAccessLockType existingAccess;

    {
        CAutoAccessControl autoAccess;

        RetailAssert(
            autoAccess.TryToLockAccess(&accessControl, alt_Remove),
            "ERROR: Auto accessor failed to acquire available access!");
        RetailAssert(
            accessControl.accessLock == alt_Remove,
            "ERROR: Access control does not indicate expected alt_Remove value!");
        RetailAssert(
            accessControl.readersCount == 1,
            "ERROR: Access control does not indicate expected reader count value of 1!");
        cout << "PASSED: First call of TryToLockAccess() has succeeded as expected!" << endl;

        RetailAssert(
            autoAccess.TryToLockAccess(&accessControl, alt_Update),
            "ERROR: Auto accessor failed to release and reacquire available access!");
        RetailAssert(
            accessControl.accessLock == alt_Update,
            "ERROR: Access control does not indicate expected alt_Update value!");
        RetailAssert(
            accessControl.readersCount == 1,
            "ERROR: Access control does not indicate expected reader count value of 1!");
        cout << "PASSED: Second call of TryToLockAccess() has succeeded as expected!" << endl;

        CAutoAccessControl secondAutoAccess;

        RetailAssert(
            !secondAutoAccess.TryToLockAccess(&accessControl, alt_Remove, existingAccess),
            "ERROR: Auto accessor managed to acquire already granted access!");
        RetailAssert(
            existingAccess == alt_Update,
            "ERROR: Unexpected existing access was returned!");
        cout << "PASSED: Cannot re-lock existing locked access!" << endl;

        RetailAssert(
            secondAutoAccess.TryToLockAccess(&secondAccessControl, alt_Remove, existingAccess),
            "ERROR: Auto accessor failed to acquire available access!");
        RetailAssert(
            secondAccessControl.accessLock == alt_Remove,
            "ERROR: Access control does not indicate expected alt_Remove value!");
        RetailAssert(
            secondAccessControl.readersCount == 1,
            "ERROR: Access control does not indicate expected reader count value of 1!");
        RetailAssert(
            existingAccess == alt_None,
            "ERROR: Unexpected existing access was returned!");
        cout << "PASSED: Can lock different unlocked access!" << endl;

        CAutoAccessControl thirdAutoAccess;

        thirdAutoAccess.MarkAccess(&accessControl);
        RetailAssert(
            accessControl.readersCount == 2,
            "ERROR: Access control does not indicate expected reader count value of 2!");
        cout << "PASSED: Can mark access on locked control!" << endl;

        thirdAutoAccess.MarkAccess(&secondAccessControl);
        RetailAssert(
            accessControl.readersCount == 1,
            "ERROR: Access control does not indicate expected reader count value of 1!");
        RetailAssert(
            secondAccessControl.readersCount == 2,
            "ERROR: Access control does not indicate expected reader count value of 2!");
        cout << "PASSED: Can release and mark access on different locked control!" << endl;
    }

    RetailAssert(
        accessControl.accessLock == alt_None,
        "ERROR: Access control has not reverted to expected alt_None value!");
    RetailAssert(
        accessControl.readersCount == 0,
        "ERROR: Access control does not indicate expected reader count value of 0!");
    RetailAssert(
        secondAccessControl.accessLock == alt_None,
        "ERROR: Access control has not reverted to expected alt_None value!");
    RetailAssert(
        accessControl.readersCount == 0,
        "ERROR: Access control does not indicate expected reader count value of 0!");

    {
        CAutoAccessControl autoAccess;

        autoAccess.MarkAccess(&accessControl);
        RetailAssert(
            accessControl.accessLock == alt_None,
            "ERROR: Access control does not indicate expected alt_None value!");
        RetailAssert(
            accessControl.readersCount == 1,
            "ERROR: Access control does not indicate expected reader count value of 1!");
        cout << "PASSED: MarkAccess() has succeeded as expected!" << endl;

        RetailAssert(
            autoAccess.TryToLockAccess(alt_Remove),
            "ERROR: Auto accessor failed to acquire available access!");
        RetailAssert(
            accessControl.accessLock == alt_Remove,
            "ERROR: Access control does not indicate expected alt_Remove value!");
        RetailAssert(
            accessControl.readersCount == 1,
            "ERROR: Access control does not indicate expected reader count value of 1!");
        cout << "PASSED: TryToLockAccess() has succeeded as expected!" << endl;

        autoAccess.ReleaseAccess();
        RetailAssert(
            accessControl.accessLock == alt_None,
            "ERROR: Access control does not indicate expected alt_None value!");
        RetailAssert(
            accessControl.readersCount == 0,
            "ERROR: Access control does not indicate expected reader count value of 0!");
        cout << "PASSED: ReleaseAccess() has succeeded as expected!" << endl;

        // Re-acquire access lock so we can test releasing lock only.
        RetailAssert(
            autoAccess.TryToLockAccess(&accessControl, alt_Remove),
            "ERROR: Auto accessor failed to acquire available access!");
        RetailAssert(
            accessControl.accessLock == alt_Remove,
            "ERROR: Access control does not indicate expected alt_Remove value!");
        RetailAssert(
            accessControl.readersCount == 1,
            "ERROR: Access control does not indicate expected reader count value of 1!");
        cout << "PASSED: TryToLockAccess() has succeeded as expected!" << endl;

        autoAccess.ReleaseAccessLock();
        RetailAssert(
            accessControl.accessLock == alt_None,
            "ERROR: Access control does not indicate expected alt_None value!");
        RetailAssert(
            accessControl.readersCount == 1,
            "ERROR: Access control does not indicate expected reader count value of 1!");
        cout << "PASSED: ReleaseAccessLock() has succeeded as expected!" << endl;
    }

    RetailAssert(
        accessControl.accessLock == alt_None,
        "ERROR: Access control has not reverted to expected alt_None value!");
    RetailAssert(
        accessControl.readersCount == 0,
        "ERROR: Access control does not indicate expected reader count value of 0!");

    cout << endl << DebugOutputSeparatorLineStart << endl;
    cout << "*** EAccessControl tests ended ***" << endl;
    cout << DebugOutputSeparatorLineEnd << endl;
}
