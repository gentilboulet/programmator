#include <ctime>
#include <tuple>
#include <string>
#include <set>

#include <event.h>
#include <place.h>

#pragma once

class Screening
{
    public:
        Screening() = delete;
        Screening(Screening&& ) = default;
        ~Screening() = default;
        
        bool operator<(const Screening& rhs) const
        {
            return std::tie(m_event, m_start, m_stop) < std::tie(rhs.m_event, rhs.m_start, rhs.m_stop);
        }

        static void init_tree(boost::filesystem::path const&);
        static void new_screenings(Event const&);
    private:
        Screening(Event const&, Place const&, std::string const&, std::string const&);

        const Event & m_event;        

        std::time_t m_start;
        std::time_t m_stop;

        static std::set<Screening> m_screenings;

};
