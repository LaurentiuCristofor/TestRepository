////////////////////////////////////////////////////////////////////////////////////////////////////
/// (c) Laurentiu Cristofor
/// This file is made available under the MIT license.
/// Do not use it if you have not received an associated LICENSE file.
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <sstream>

namespace LaurentiuCristofor
{

class AssertionFailure : public std::exception
{
public:

    AssertionFailure(std::string message)
    {
        m_message = message;
    }

    virtual const char* what() const throw()
    {
        return m_message.c_str();
    }

public:

    std::string m_message;
};

__attribute__((noreturn)) inline void ThrowAssertionFailure(
    const char* message, const char* file, size_t line, const char* function)
{
    std::stringstream messageStream;
    messageStream << "Assertion failed in " << file << "::" << function << "(): line " << line << ": " << message;
    throw AssertionFailure(messageStream.str());
}

// Retail asserts are meant for important conditions that indicate internal errors.
// They help us surface issues early, at the source.
#define ASSERT(_condition, _message) \
if (__builtin_expect(!static_cast<bool>(_condition), false)) \
{ \
    ThrowAssertionFailure(_message, __FILE__, __LINE__, __func__); \
}

} // LaurentiuCristofor
