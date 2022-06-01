////////////////////////////////////////////////////////////////////////////////////////////////////
/// (c) Laurentiu Cristofor
/// This file is made available under the MIT license.
/// Do not use it if you have not received an associated LICENSE file.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "Constants.hpp"
#include "Assert.hpp"
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
    AccessType existingAccess;

    {
        CAutoAccessControl autoAccess;

        ASSERT(
            autoAccess.TryToLockAccess(&accessControl, AccessType::Remove),
            "ERROR: Auto accessor failed to acquire available access!");
        ASSERT(
            accessControl.accessLock == AccessType::Remove,
            "ERROR: Access control does not indicate expected AccessType::Remove value!");
        ASSERT(
            accessControl.readersCount == 1,
            "ERROR: Access control does not indicate expected reader count value of 1!");
        cout << "PASSED: First call of TryToLockAccess() has succeeded as expected!" << endl;

        ASSERT(
            autoAccess.TryToLockAccess(&accessControl, AccessType::Update),
            "ERROR: Auto accessor failed to release and reacquire available access!");
        ASSERT(
            accessControl.accessLock == AccessType::Update,
            "ERROR: Access control does not indicate expected AccessType::Update value!");
        ASSERT(
            accessControl.readersCount == 1,
            "ERROR: Access control does not indicate expected reader count value of 1!");
        cout << "PASSED: Second call of TryToLockAccess() has succeeded as expected!" << endl;

        CAutoAccessControl secondAutoAccess;

        ASSERT(
            !secondAutoAccess.TryToLockAccess(&accessControl, AccessType::Remove, existingAccess),
            "ERROR: Auto accessor managed to acquire already granted access!");
        ASSERT(
            existingAccess == AccessType::Update,
            "ERROR: Unexpected existing access was returned!");
        cout << "PASSED: Cannot re-lock existing locked access!" << endl;

        ASSERT(
            secondAutoAccess.TryToLockAccess(&secondAccessControl, AccessType::Remove, existingAccess),
            "ERROR: Auto accessor failed to acquire available access!");
        ASSERT(
            secondAccessControl.accessLock == AccessType::Remove,
            "ERROR: Access control does not indicate expected AccessType::Remove value!");
        ASSERT(
            secondAccessControl.readersCount == 1,
            "ERROR: Access control does not indicate expected reader count value of 1!");
        ASSERT(
            existingAccess == AccessType::None,
            "ERROR: Unexpected existing access was returned!");
        cout << "PASSED: Can lock different unlocked access!" << endl;

        CAutoAccessControl thirdAutoAccess;

        thirdAutoAccess.MarkAccess(&accessControl);
        ASSERT(
            accessControl.readersCount == 2,
            "ERROR: Access control does not indicate expected reader count value of 2!");
        cout << "PASSED: Can mark access on locked control!" << endl;

        thirdAutoAccess.MarkAccess(&secondAccessControl);
        ASSERT(
            accessControl.readersCount == 1,
            "ERROR: Access control does not indicate expected reader count value of 1!");
        ASSERT(
            secondAccessControl.readersCount == 2,
            "ERROR: Access control does not indicate expected reader count value of 2!");
        cout << "PASSED: Can release and mark access on different locked control!" << endl;
    }

    ASSERT(
        accessControl.accessLock == AccessType::None,
        "ERROR: Access control has not reverted to expected AccessType::None value!");
    ASSERT(
        accessControl.readersCount == 0,
        "ERROR: Access control does not indicate expected reader count value of 0!");
    ASSERT(
        secondAccessControl.accessLock == AccessType::None,
        "ERROR: Access control has not reverted to expected AccessType::None value!");
    ASSERT(
        accessControl.readersCount == 0,
        "ERROR: Access control does not indicate expected reader count value of 0!");

    {
        CAutoAccessControl autoAccess;

        autoAccess.MarkAccess(&accessControl);
        ASSERT(
            accessControl.accessLock == AccessType::None,
            "ERROR: Access control does not indicate expected AccessType::None value!");
        ASSERT(
            accessControl.readersCount == 1,
            "ERROR: Access control does not indicate expected reader count value of 1!");
        cout << "PASSED: MarkAccess() has succeeded as expected!" << endl;

        ASSERT(
            autoAccess.TryToLockAccess(AccessType::Remove),
            "ERROR: Auto accessor failed to acquire available access!");
        ASSERT(
            accessControl.accessLock == AccessType::Remove,
            "ERROR: Access control does not indicate expected AccessType::Remove value!");
        ASSERT(
            accessControl.readersCount == 1,
            "ERROR: Access control does not indicate expected reader count value of 1!");
        cout << "PASSED: TryToLockAccess() has succeeded as expected!" << endl;

        autoAccess.ReleaseAccess();
        ASSERT(
            accessControl.accessLock == AccessType::None,
            "ERROR: Access control does not indicate expected AccessType::None value!");
        ASSERT(
            accessControl.readersCount == 0,
            "ERROR: Access control does not indicate expected reader count value of 0!");
        cout << "PASSED: ReleaseAccess() has succeeded as expected!" << endl;

        // Re-acquire access lock so we can test releasing lock only.
        ASSERT(
            autoAccess.TryToLockAccess(&accessControl, AccessType::Remove),
            "ERROR: Auto accessor failed to acquire available access!");
        ASSERT(
            accessControl.accessLock == AccessType::Remove,
            "ERROR: Access control does not indicate expected AccessType::Remove value!");
        ASSERT(
            accessControl.readersCount == 1,
            "ERROR: Access control does not indicate expected reader count value of 1!");
        cout << "PASSED: TryToLockAccess() has succeeded as expected!" << endl;

        autoAccess.ReleaseAccessLock();
        ASSERT(
            accessControl.accessLock == AccessType::None,
            "ERROR: Access control does not indicate expected AccessType::None value!");
        ASSERT(
            accessControl.readersCount == 1,
            "ERROR: Access control does not indicate expected reader count value of 1!");
        cout << "PASSED: ReleaseAccessLock() has succeeded as expected!" << endl;
    }

    ASSERT(
        accessControl.accessLock == AccessType::None,
        "ERROR: Access control has not reverted to expected AccessType::None value!");
    ASSERT(
        accessControl.readersCount == 0,
        "ERROR: Access control does not indicate expected reader count value of 0!");

    cout << endl << DebugOutputSeparatorLineStart << endl;
    cout << "*** EAccessControl tests ended ***" << endl;
    cout << DebugOutputSeparatorLineEnd << endl;
}
