#include "boost/program_options.hpp"

#include <iostream>
#include <string>

namespace 
{
    const int SUCCESS = 0;
    const int ERROR_IN_COMMAND_LINE  = 1;
    const int ERROR_UNHANDLED_EXCEPTION = 2;
}

int main(int argc, char** argv) 
{
    try 
    {
        namespace po = boost::program_options; 

        po::options_description cmd_line("Command line options");
        cmd_line.add_options() 
            ("help,h", "Print help messages") 
            ("verbose,v", "print words with verbosity") 
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

            po::notify(vm); 
        }    
        catch(po::error& e) 
        { 
            std::cerr << "ERROR  : " << e.what() << std::endl << std::endl; 
            std::cerr << cmd_line << std::endl; 
            return ERROR_IN_COMMAND_LINE; 
        } 
    }
    catch(std::exception& e) 
    { 
        std::cerr << "Unhandled Exception reached the top of main: " 
            << e.what() << ", application will now exit" << std::endl; 
        return ERROR_UNHANDLED_EXCEPTION; 

    } 
    return SUCCESS;
}
