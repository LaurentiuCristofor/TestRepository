////////////////////////////////////////////////////////////////////////////////////////////////////
/// (c) Laurentiu Cristofor
/// This file is made available under the MIT license.
/// Do not use it if you have not received an associated LICENSE file.
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstddef>
#include <cstdint>

#include "AccessControl.hpp"

namespace LaurentiuCristofor
{

// Common structure of an in-memory linked list node
// that includes an AccessControl field for synchronization.
struct ListNode
{
    size_t next;
    AccessControl accessControl;

    // Some kind of payload.
    uint64_t payload;

    void Clear()
    {
        next = 0;
        accessControl.Clear();
    }
};

// Encapsulates the set of variables needed for iterating over a list.
struct IterationContext
{
    ListNode* pPreviousRecord;
    CAutoAccessControl autoAccessPreviousRecord;

    ListNode* pCurrentRecord;
    CAutoAccessControl autoAccessCurrentRecord;

    IterationContext()
    {
        pPreviousRecord = nullptr;
        pCurrentRecord = nullptr;
    }
};

} // LaurentiuCristofor
