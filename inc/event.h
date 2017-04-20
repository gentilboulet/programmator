#include <boost/filesystem.hpp>
#include <tuple>
#include <string>
#include <set>

#include <place.h>

#pragma once

class Event 
{
    public:
        static const Event& new_event(boost::filesystem::path const&);
        
        Event(Event&&) = default;
        ~Event() = default;
        bool operator<(const Event& rhs) const
        {
            return std::tie(m_program) < std::tie(rhs.m_program);
        }

        boost::filesystem::path const& path() const { return m_path; };
        std::string const& program() const { return m_program; };
        std::string const& url() const { return m_url; };
    private:

        Event(boost::filesystem::path const&);

        Event() = delete;

        boost::filesystem::path m_path;
        std::string m_url;
        std::string m_program;
        
        static std::set<Event> m_events;
};
