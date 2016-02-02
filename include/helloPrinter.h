#ifndef HELLO_PRINTER_H
#define HELLO_PRINTER_H

#include <string>
#include <stdexcept>
using namespace std;

class HelloPrinter
{
    public:
    string Hello();
    void FailHorribly();
};

#endif
