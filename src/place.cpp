#include <place.h>

std::set<Place> Place::m_disallowed;
        
void Place::disallow_places(std::vector<std::string> const& l_places)
{
    for(auto & l_where : l_places)
    {
        m_disallowed.insert(Place{ l_where } );
    }
}


