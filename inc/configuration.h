#include <boost/filesystem.hpp>
#include <vector>
#include <string>

#pragma once

class Configuration
{
    public:
        Configuration(const boost::filesystem::path&);
        Configuration() = delete;
        ~Configuration() = default;

        const boost::filesystem::path& screenings_path() const { return m_screenings; };
        const std::vector<std::string>& disallowed_places() const { return m_disallowed_places; };
    private:
        boost::filesystem::path m_config_json;
        boost::filesystem::path m_screenings;
        std::vector<std::string> m_disallowed_places;
};
