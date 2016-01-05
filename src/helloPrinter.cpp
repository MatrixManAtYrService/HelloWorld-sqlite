#include <string>
#include <stdexcept>
#include "helloPrinter.h"
using namespace std;

string HelloPrinter::Hello()
{
    return "Hello world!\n";
}

void HelloPrinter::FailHorribly()
{
    throw std::out_of_range("Useful Error Message");
}
