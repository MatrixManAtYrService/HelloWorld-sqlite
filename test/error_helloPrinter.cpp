#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "HelloPrinter output tests"

#include <string>
#include <stdexcept>
#include "helloPrinter.h"

#include <boost/test/unit_test.hpp> //include this last

// Does HelloPrinter.Hello() throw an exception?
BOOST_AUTO_TEST_CASE(NoError)
{
    // throwing an exception will cause a test to fail

    HelloPrinter printer;
    string printedString = printer.Hello();

    // for example, try un-commenting this:
    //printer.FailHorribly();
}

// That is, unless the exception was expected
BOOST_AUTO_TEST_CASE(Error)
{
    HelloPrinter printer;
    BOOST_CHECK_THROW(printer.FailHorribly(), std::out_of_range);

    //This test passes, unless you un-comment this:
    //printer.FailHorribly();
}
