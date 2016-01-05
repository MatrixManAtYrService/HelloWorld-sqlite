#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "HelloPrinter output tests"

#include <string>
#include "helloPrinter.h"

#include <boost/test/unit_test.hpp> //include this last

// Does HelloPrinter actually say hello?
BOOST_AUTO_TEST_CASE(SayHello)
{
    HelloPrinter printer;
    string printedString = printer.Hello();
    BOOST_CHECK_EQUAL(printedString,"Hello world!\n");
}
