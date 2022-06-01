////////////////////////////////////////////////////////////////////////////////////////////////////
/// (c) Laurentiu Cristofor
/// This file is made available under the MIT license.
/// Do not use it if you have not received an associated LICENSE file.
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace LaurentiuCristofor
{

// Values that can indicate the access desired for resources.
enum class AccessType : int8_t
{
    None = 0,

    Read = 1,
    Insert = 2,
    Update = 3,
    UpdateRemove = 4,
    Remove = 5,
};

struct AccessControl
{
    uint32_t readersCount;
    AccessType accessLock;

    AccessControl()
    {
        Clear();
    }

    void Clear()
    {
        readersCount = 0;
        accessLock = AccessType::None;
    }
};

// A class for access synchronization. It can be used to implement spinlocks.
//
// This class manipulates the access control object that is associated to a resource.
//
// There are 2 main operations:
// (i) Marking read access - this is a ref-count that can be used to prevent the
// destruction of a resource until all readers have finished accessing it.
// But note that because a resource can be changed between when its access control
// was first read and when it was updated, some additional checks need to be done
// after the read access was marked.
// (ii) Locking access - this is an exclusive lock that prevents other threads
// from operating on the resource.
//
class CAutoAccessControl
{
private:

    AccessControl* m_pAccessControl;
    AccessType m_lockedAccess;
    bool m_hasMarkedAccess;
    bool m_hasLockedAccess;

public:

    CAutoAccessControl();
    ~CAutoAccessControl();

    void MarkAccess(AccessControl* pAccessControl);

    bool TryToLockAccess(AccessControl* pAccessControl, AccessType wantedAccess, AccessType& existingAccess);
    bool TryToLockAccess(AccessControl* pAccessControl, AccessType wantedAccess);

    // These versions can be called after an initial MarkAccess call.
    bool TryToLockAccess(AccessType wantedAccess, AccessType& existingAccess);
    bool TryToLockAccess(AccessType wantedAccess);

    // Methods for releasing all access or just the access lock.
    void ReleaseAccess();
    void ReleaseAccessLock();

    bool HasMarkedAccess()
    {
        return m_hasMarkedAccess;
    }

    bool HasLockedAccess()
    {
        return m_hasLockedAccess;
    }

private:

    void Clear();
};

} // LaurentiuCristofor.Synchronization
