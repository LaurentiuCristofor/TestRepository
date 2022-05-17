////////////////////////////////////////////////////////////////////////////////////////////////////
/// (c) Laurentiu Cristofor
/// This file is made available under the MIT license.
/// Do not use it if you have not received an associated LICENSE file.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stddef.h>
#include <stdint.h>

#include "RetailAssert.hpp"
#include "AccessControl.hpp"

using namespace LaurentiuCristofor;

CAutoAccessControl::CAutoAccessControl()
{
    Clear();
}

CAutoAccessControl::~CAutoAccessControl()
{
    ReleaseAccess();
}

void CAutoAccessControl::Clear()
{
    m_pAccessControl = nullptr;
    m_lockedAccess = alt_None;
    m_hasMarkedAccess = false;
    m_hasLockedAccess = false;
}

void CAutoAccessControl::MarkAccess(AccessControl* pAccessControl)
{
    RetailAssert(pAccessControl != nullptr, "No access control was provided!");
    RetailAssert(pAccessControl->readersCount != UINT32_MAX, "Readers count has maxed up and will overflow!");

    ReleaseAccess();

    m_pAccessControl = pAccessControl;

    __sync_fetch_and_add(&m_pAccessControl->readersCount, 1);
    m_hasMarkedAccess = true;
}

bool CAutoAccessControl::TryToLockAccess(
    AccessControl* pAccessControl,
    EAccessLockType wantedAccess,
    EAccessLockType& existingAccess)
{
    RetailAssert(wantedAccess != alt_None, "Invalid wanted access!");

    MarkAccess(pAccessControl);

    m_lockedAccess = wantedAccess;
    existingAccess = __sync_val_compare_and_swap(&m_pAccessControl->accessLock, alt_None, m_lockedAccess);
    m_hasLockedAccess = (existingAccess == alt_None);

    return m_hasLockedAccess;
}

bool CAutoAccessControl::TryToLockAccess(AccessControl* pAccessControl, EAccessLockType wantedAccess)
{
    EAccessLockType existingAccess;

    return TryToLockAccess(pAccessControl, wantedAccess, existingAccess);
}

bool CAutoAccessControl::TryToLockAccess(
    EAccessLockType wantedAccess,
    EAccessLockType& existingAccess)
{
    RetailAssert(m_pAccessControl != nullptr, "Invalid call, no access control available!");
    RetailAssert(wantedAccess != alt_None, "Invalid wanted access!");

    if (m_hasLockedAccess)
    {
        return m_lockedAccess == wantedAccess;
    }

    m_lockedAccess = wantedAccess;
    existingAccess = __sync_val_compare_and_swap(&m_pAccessControl->accessLock, alt_None, m_lockedAccess);
    m_hasLockedAccess = (existingAccess == alt_None);

    return m_hasLockedAccess;
}

bool CAutoAccessControl::TryToLockAccess(EAccessLockType wantedAccess)
{
    EAccessLockType existingAccess;

    return TryToLockAccess(wantedAccess, existingAccess);
}

void CAutoAccessControl::ReleaseAccess()
{
    if (m_pAccessControl == nullptr)
    {
        return;
    }

    ReleaseAccessLock();

    if (m_hasMarkedAccess)
    {
        __sync_fetch_and_sub(&m_pAccessControl->readersCount, 1);
        m_hasMarkedAccess = false;
    }

    m_pAccessControl = nullptr;
}

void CAutoAccessControl::ReleaseAccessLock()
{
    if (m_pAccessControl == nullptr)
    {
        return;
    }

    if (m_hasLockedAccess)
    {
        RetailAssert(
            __sync_bool_compare_and_swap(&m_pAccessControl->accessLock, m_lockedAccess, alt_None),
            "Failed to release access lock!");
        m_hasLockedAccess = false;
    }

    m_lockedAccess = alt_None;
}
