#include <set>
#include <string>
#include <tuple>
#include <vector>

#pragma once

class Place
{
    public:
        Place() = delete;
        ~Place() = default;

        Place(std::string const& a_where) : m_where{a_where} {} ;
        Place(std::string && a_where) : m_where{a_where} {} ;

        bool operator<(const Place& rhs) const
        {
            return std::tie(m_where) < std::tie(rhs.m_where);
        }

        static bool is_disallowed(Place const& a_where) { return m_disallowed.find(a_where)!=m_disallowed.end(); };
        static void disallow_places(std::vector<std::string> const&);
    private:
        std::string m_where;
        static std::set<Place> m_disallowed;
};
