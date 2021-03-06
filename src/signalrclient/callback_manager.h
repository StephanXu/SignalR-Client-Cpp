// Copyright (c) .NET Foundation. All rights reserved.
// Licensed under the Apache License, Version 2.0. See License.txt in the project root for license information.

#pragma once

#include <atomic>
#include <unordered_map>
#include <functional>
#include <mutex>
#include "signalrclient/signalr_value.h"

namespace signalr
{
    class callback_manager
    {
    public:
        explicit callback_manager(const signalr::value& dtor_error);
        ~callback_manager();

        callback_manager(const callback_manager&) = delete;
        callback_manager& operator=(const callback_manager&) = delete;

        std::string register_callback(const std::function<void(const signalr::value&)>& callback);
        bool invoke_callback(const std::string& callback_id, const signalr::value& arguments, bool remove_callback);
        bool remove_callback(const std::string& callback_id);
        void clear(const signalr::value& arguments);

    private:
        std::atomic<int> m_id { 0 };
        std::unordered_map<std::string, std::function<void(const signalr::value&)>> m_callbacks;
        std::mutex m_map_lock;
        const signalr::value m_dtor_clear_arguments;

        std::string get_callback_id();
    };
}
