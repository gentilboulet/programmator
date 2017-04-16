#include <boost/filesystem.hpp>
#include <vector>

#pragma once

class Event 
{
    public:
        static void new_event(boost::filesystem::path const&);
        ~Event() = default;

    private:
        Event(boost::filesystem::path const&);
        Event() = delete;

        boost::filesystem::path m_path;
        static std::vector<Event> m_events;
};
