#include <logger.h>
#include <iostream>

Log::level Log::m_static_min_level = Log::level::debug;
std::mutex Log::m_static_mutex;

std::string to_string(Log::level level)
{
    switch(level)
    {
        case Log::level::debug: return "debug";
        case Log::level::warning: return "warning";
        case Log::level::error: return "error";
    }
}

Log& Log::operator<<(const std::string& a_what)
{
    if(!m_enable) return *this;

    if(m_level >= m_static_min_level)
    {
        std::lock_guard<std::mutex> guard(m_static_mutex);
        std::cout << "["<<to_string(m_level) << "]";
        std::cout << " " << m_class << "::"<<m_function<< " > " ;
        std::cout << a_what << std::endl;
    }
    
    if(m_level == Log::level::error)
    {
        // U can't silence errors
        std::cerr << a_what << std::endl;
    }
    return *this;
}
