////////////////////////////////////////////////////////////////////////////////////////////////////
/// (c) Laurentiu Cristofor
/// This file is made available under the MIT license.
/// Do not use it if you have not received an associated LICENSE file.
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <exception>
#include <string>

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

} // LaurentiuCristofor
