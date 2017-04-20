#include <configuration.h>
#include <logger.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <stdexcept>

namespace pt=boost::property_tree;
namespace fs=boost::filesystem;

Configuration::Configuration(const fs::path& a_path) : m_config_json{a_path}
{
    LOGGERS("Configuration()","Configuration()");

    if(!boost::filesystem::exists( m_config_json) )
    {
        log_error << "Configuration file not found : " + m_config_json.string();
        throw std::runtime_error("Configuration file not found : " + m_config_json.string() );
    }

    fs::ifstream l_file{ m_config_json };

    pt::ptree l_ptree;
    pt::read_json(l_file, l_ptree);

    m_screenings = fs::path{ l_ptree.get<std::string> ("screenings") };
    
    log_debug << "screenings path : " + m_screenings.string();
}
