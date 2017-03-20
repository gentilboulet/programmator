#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE UT_Cells
#endif
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( UT_Empty )

BOOST_AUTO_TEST_CASE( True )
{
    BOOST_TEST( true );
}

BOOST_AUTO_TEST_SUITE_END()
