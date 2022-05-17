////////////////////////////////////////////////////////////////////////////////////////////////////
/// (c) Laurentiu Cristofor
/// This file is made available under the MIT license.
/// Do not use it if you have not received an associated LICENSE file.
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>

#include "RetailAssertException.hpp"

namespace LaurentiuCristofor
{

// Retail asserts are meant for important conditions that indicate internal errors.
// They help us surface issues early, at the source.
inline void RetailAssert(bool condition, std::string message)
{
    if (!condition)
    {
        throw RetailAssertException(message);
    }
}

} // LaurentiuCristofor
