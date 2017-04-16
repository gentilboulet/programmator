#include <screening.h>
#include <logger.h>
#include <event.h>

#include <vector>

void Screening::init_tree(boost::filesystem::path const& a_path)
{
    Log log_info{"Screening","init_tree()", Log::level::info};
    Log log_error{"Screening","init_tree()", Log::level::error};

    log_info << std::string("Reading from ") + a_path.string();


    std::vector<boost::filesystem::path> l_json_vec;    
    boost::filesystem::directory_iterator it_begin(a_path), it_end;
    for(auto it = it_begin; it!=it_end; it++)
    {
        boost::filesystem::path l_file(*it);
        if(l_file.extension() == ".json")
        {
            log_info << "json file found " + l_file.string();
            l_json_vec.push_back(l_file);
        }
    }

    for(auto json : l_json_vec)
    {
        Event::new_event(json);
    } 
}
