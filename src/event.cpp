#include <event.h>
#include <logger.h>
#include <screening.h>

#include <stdexcept>
#include <algorithm>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <stdexcept>

#define LOGTHROW(what) { const std::string _err { what } ; log_error << _err ; throw std::runtime_error(_err); }

namespace pt=boost::property_tree;
namespace fs=boost::filesystem;

std::set<Event> Event::m_events;

Event::Event(fs::path const& a_path) 
    : m_path(a_path)
{
    LOGGERS("Event","Event()");
    log_debug << "arg = " + a_path.string();

    if(a_path.extension() != ".json") 
        LOGTHROW("Wrong extension for " + m_path.string() );

    if(! fs::exists(m_path) )
        LOGTHROW( "File " + m_path.string() + " does not exist" );

    fs::ifstream l_file{ m_path };
    if(! l_file.is_open())
        LOGTHROW( "Cannot open file " + m_path.string() );

    pt::ptree l_ptree;
    pt::read_json(l_file, l_ptree);

    m_program = l_ptree.get<std::string>("programme");
    m_url = l_ptree.get<std::string>("url");

    for(auto const &seance : l_ptree.get_child("seances.") )
    {
        std::string l_where { seance.second.get<std::string>("where") };
        std::string l_day { seance.second.get<std::string>("day") };
        std::string l_time { seance.second.get<std::string>("time") };
    
        log_debug << " new screening at "+l_where+" on " + l_day + " at " + l_time ;
    }

    log_debug << " end of constructor : m_program " + m_program;
    log_debug << " end of constructor : m_url " + m_url;
}

const Event& Event::new_event(fs::path const& a_path)
{
    LOGGERS("Event","new_event()");
    log_debug << "arg = " + a_path.string();

    auto ret = m_events.insert(Event{a_path});
    log_debug << "number of events ? " + std::to_string(m_events.size());

    if(ret.second)
        return *ret.first;
    else
        LOGTHROW("Event already present");
}
