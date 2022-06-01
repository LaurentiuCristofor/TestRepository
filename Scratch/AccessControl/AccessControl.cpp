////////////////////////////////////////////////////////////////////////////////////////////////////
/// (c) Laurentiu Cristofor
/// This file is made available under the MIT license.
/// Do not use it if you have not received an associated LICENSE file.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstddef>
#include <cstdint>

#include "Assert.hpp"
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
    m_lockedAccess = AccessType::None;
    m_hasMarkedAccess = false;
    m_hasLockedAccess = false;
}

void CAutoAccessControl::MarkAccess(
    AccessControl* pAccessControl)
{
    ASSERT(pAccessControl != nullptr, "No access control was provided!");
    ASSERT(pAccessControl->readersCount != UINT32_MAX, "Readers count has maxed up and will overflow!");

    ReleaseAccess();

    m_pAccessControl = pAccessControl;

    __sync_fetch_and_add(&m_pAccessControl->readersCount, 1);
    m_hasMarkedAccess = true;
}

bool CAutoAccessControl::TryToLockAccess(
    AccessControl* pAccessControl,
    AccessType wantedAccess,
    AccessType& existingAccess)
{
    MarkAccess(pAccessControl);

    return TryToLockAccess(wantedAccess, existingAccess);
}

bool CAutoAccessControl::TryToLockAccess(
    AccessControl* pAccessControl,
    AccessType wantedAccess)
{
    AccessType existingAccess;

    return TryToLockAccess(pAccessControl, wantedAccess, existingAccess);
}

bool CAutoAccessControl::TryToLockAccess(
    AccessType wantedAccess,
    AccessType& existingAccess)
{
    ASSERT(m_pAccessControl != nullptr, "Invalid call, no access control available!");
    ASSERT(wantedAccess != AccessType::None, "Invalid wanted access!");

    existingAccess = m_pAccessControl->accessLock;

    if (m_hasLockedAccess)
    {
        return m_lockedAccess == wantedAccess;
    }

    existingAccess = static_cast<AccessType>(__sync_val_compare_and_swap(
        reinterpret_cast<int8_t*>(&m_pAccessControl->accessLock),
        static_cast<int8_t>(AccessType::None),
        static_cast<int8_t>(wantedAccess)));
    m_hasLockedAccess = (existingAccess == AccessType::None);
    if (m_hasLockedAccess)
    {
        m_lockedAccess = wantedAccess;
    }

    return m_hasLockedAccess;
}

bool CAutoAccessControl::TryToLockAccess(
    AccessType wantedAccess)
{
    AccessType existingAccess;

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
        ASSERT(
            __sync_bool_compare_and_swap(
                reinterpret_cast<int8_t*>(&m_pAccessControl->accessLock),
                static_cast<int8_t>(m_lockedAccess),
                static_cast<int8_t>(AccessType::None)),
            "Failed to release access lock!");
        m_hasLockedAccess = false;
    }

    m_lockedAccess = AccessType::None;
}
