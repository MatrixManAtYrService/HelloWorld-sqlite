//Link to Boost
#define BOOST_TEST_DYN_LINK

//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "Hello"

//VERY IMPORTANT - include this last
#include <boost/test/unit_test.hpp>

#include "helloPrinter.h"
// ------------- Tests Follow --------------

//Name your test cases for what they test
BOOST_AUTO_TEST_CASE( values )
{
  HelloPrinter printer;

//Use BOOST_CHECK_EQUAL if you want the values to be 
//printed out if they mismatch
  BOOST_CHECK_EQUAL(printer.Hello(), "Hello world!");
}
