#include "helloPrinter.h"
#include <iostream>
using namespace std;

int main()
{
	HelloPrinter printer;
    string something = printer.Hello();

	cout << something;
}
