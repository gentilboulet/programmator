#include <boost/filesystem.hpp>

#pragma once

class Configuration
{
    public:
        Configuration(const boost::filesystem::path&);
        Configuration() = delete;
        ~Configuration() = default;

        const boost::filesystem::path screenings_path() const { return m_screenings; };
    private:
        boost::filesystem::path m_config_json;
        boost::filesystem::path m_screenings;
};
