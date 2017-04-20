#include <screening.h>
#include <logger.h>
#include <event.h>

#include <vector>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <stdexcept>

#define LOGTHROW(what) { const std::string _err { what } ; log_error << _err ; throw std::runtime_error(_err); }

namespace pt=boost::property_tree;
namespace fs=boost::filesystem;

std::set<Screening> Screening::m_screenings;

void Screening::init_tree(boost::filesystem::path const& a_path)
{
    LOGGERS("Screening","init_tree()");
    log_debug << "arg =" + a_path.string();

    std::vector<boost::filesystem::path> l_json_vec;    
    boost::filesystem::directory_iterator it_begin(a_path), it_end;
    for(auto it = it_begin; it!=it_end; it++)
    {
        boost::filesystem::path l_file(*it);
        if(l_file.extension() == ".json")
        {
            l_json_vec.push_back(l_file);
        }
    }

    for(auto json : l_json_vec)
    {
        const Event& l_ref = Event::new_event(json);
        Screening::new_screenings(l_ref);
    } 
}

void Screening::new_screenings(const Event & a_event)
{
    LOGGERS("Screening","new_screenings()");
    log_debug << "arg = Event("+a_event.program()+")";

    fs::path const& l_path = a_event.path();
 
    if(l_path.extension() != ".json") 
        LOGTHROW("Wrong extension for " + l_path.string() );

    if(!fs::exists(l_path) )
        LOGTHROW( "File " + l_path.string() + " does not exist" );

    fs::ifstream l_file{ l_path };
    if(! l_file.is_open())
        LOGTHROW( "Cannot open file " + l_path.string() );
    
    pt::ptree l_ptree;
    pt::read_json(l_file, l_ptree);

    for(auto const &seance : l_ptree.get_child("seances.") )
    {
        Place l_where { seance.second.get<std::string>("where") };
        std::string l_day { seance.second.get<std::string>("day") };
        std::string l_time { seance.second.get<std::string>("time") };
    
        if( Place::is_disallowed(l_where) )
        {   
            log_debug << "Disallowed screening";
            continue;
        }

        auto ret = m_screenings.insert(Screening{ a_event , l_where, l_day, l_time });
        if(!ret.second)
            LOGTHROW("Error inserting a screening for " + a_event.program() );
    }
}

Screening::Screening(Event const& a_event, Place const& a_where, std::string const& a_day, std::string const& a_time) :
        m_event{a_event}
{
    LOGGERS("Screening","Screening()");
    log_debug << "arg = Event(" + a_event.program()+")";
    log_debug << "arg = day " + a_day;
    log_debug << "arg = time " + a_time;

    
}
