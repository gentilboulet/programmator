#include <mutex>
#include <string>

#pragma once

class Log
{
    public:
        enum class level {debug, warning, info, error};
        static void set_min_level(level a_min_level) { std::lock_guard<std::mutex> guard(m_static_mutex); m_static_min_level = a_min_level; };
    private:
        static std::mutex m_static_mutex;
        static level m_static_min_level;

    public:

        Log(const std::string& a_class, const std::string& a_func, Log::level a_level= Log::level::warning) 
            :   m_level(a_level),
                m_class(a_class),
                m_function(a_func)
        {};

        Log& operator<<(const std::string& a_what);

        Log() = delete;        
        ~Log() = default;
    private:
        level m_level;
        std::string m_class;
        std::string m_function;
};
