// Copyright (c) .NET Foundation. All rights reserved.
// Licensed under the Apache License, Version 2.0. See License.txt in the project root for license information.

#pragma once

#include <functional>
#include <cctype>

namespace signalr
{
    // Note: These functions are not pretending to be all-purpose helpers for case insensitive string comparison. Rather
    // we use them to compare hub and hub method names which are expected to be almost exclusively ASCII and this is the
    // simplest thing that would work without having to take dependencies on third party libraries.
    struct case_insensitive_equals : std::binary_function<std::string, std::string, bool>
    {
        bool operator()(const std::string& s1, const std::string& s2) const
        {
            if (s1.length() != s2.length())
            {
                return false;
            }

            for (int i = 0; i < s1.size(); ++i)
            {
                if (std::toupper(s1[i]) != std::toupper(s2[i]))
                {
                    return false;
                }
            }

            return true;
        }
    };

    struct case_insensitive_hash : std::unary_function<std::string, std::size_t>
    {
        std::size_t operator()(const std::string& s) const noexcept
        {
            size_t hash = 0;
            std::hash<size_t> hasher;
            for (const auto& c : s)
            {
                hash ^= hasher(std::toupper(c)) + (hash << 5) + (hash >> 2);
            }

            return hash;
        }
    };
}
