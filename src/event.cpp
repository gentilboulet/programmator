#include <event.h>
#include <logger.h>

#include <stdexcept>
#include <algorithm>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <stdexcept>

namespace pt=boost::property_tree;
namespace fs=boost::filesystem;

std::vector<Event> Event::m_events;

Event::Event(fs::path const& a_path) 
    : m_path(a_path)
{
    Log log_error{"Event","Event()", Log::level::error};
    Log log_info{"Event","Event()", Log::level::info};

    if(a_path.extension() != ".json") 
    {
        log_error << "Wrong extension for " + m_path.string();
        throw std::runtime_error("Wrong extension for " + m_path.string());
    }

    if(! fs::exists(m_path) )
    {
        log_error << "File " + m_path.string() + " does not exist";
        throw std::runtime_error("File " + m_path.string() + " does not exist");
    }
    fs::ifstream l_file{ m_path };
    if(! l_file.is_open())
    {
        log_error << "Cannot open file " + m_path.string();
        throw std::runtime_error("Cannot open file " + m_path.string());
    }

    pt::ptree l_ptree;
    pt::read_json(l_file, l_ptree);

    log_info << "Programme :" + l_ptree.get<std::string> ("programme");
}

void Event::new_event(fs::path const& a_path)
{
    Log log_debug{"Event","new_event()", Log::level::debug};
    Log log_error{"Event","new_event()", Log::level::error};

    auto it_find = std::find_if(m_events.begin(), m_events.end(), [&a_path] (const Event& e) { return e.m_path == a_path; });
    if(it_find != m_events.end())
    {
        log_error << "Already found event for " + a_path.string() ;
        return;
    }

    m_events.push_back(Event{a_path});
    log_debug << "number of events ? " + std::to_string(m_events.size());
}
