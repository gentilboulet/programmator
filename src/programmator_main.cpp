#include "boost/program_options.hpp"

#include <iostream>
#include <string>
#include <logger.h>

namespace 
{
    const int SUCCESS = 0;
    const int ERROR_IN_COMMAND_LINE  = 1;
    const int ERROR_UNHANDLED_EXCEPTION = 2;
}

int main(int argc, char** argv) 
{
    Log log_warnings {"","main", Log::level::warning};
    Log log_errors{"","main", Log::level::error};
    Log log_debug{"","main", Log::level::debug};
    try 
    {
        namespace po = boost::program_options; 
        
        po::options_description cmd_line("Command line options");
        
        std::string config_path {};
        bool verbose {false};

        cmd_line.add_options() 
            ("help,h", "Print help messages") 
            ("verbose,v", "Enable full verbosity") 
            ("config,c", po::value<std::string>(&config_path)->default_value("./config.json"), "Path to the configuration file") 
            ;

        po::variables_map vm;
        try
        {
            po::store(po::parse_command_line(argc, argv , cmd_line), vm);

            if ( vm.count("help")  ) 
            { 
                std::cout << cmd_line << std::endl;
                return SUCCESS; 
            }
            if( vm.count("verbose") )
            {
                verbose=true;
                Log::set_min_level(Log::level::debug);
            }
            po::notify(vm); 

            log_debug << "verbosity ? " + std::to_string(verbose);
            log_debug << "config_path ? " + config_path;
        }    
        catch(po::error& e) 
        { 
            log_errors << e.what() ;
            std::cout << cmd_line << std::endl;
            return ERROR_IN_COMMAND_LINE; 
        } 
    }
    catch(std::exception& e) 
    { 
        log_errors << "Unhandled Exception reached the top of main: " 
            << e.what() << ", application will now exit" ;
        return ERROR_UNHANDLED_EXCEPTION; 

    } 
    return SUCCESS;
}
